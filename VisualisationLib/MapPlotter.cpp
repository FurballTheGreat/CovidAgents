/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "MapPlotter.h"

#include <blend2d.h>
#include <GeographicLib/GeoCoords.hpp>
#include "SmallArea.h"
#include <png.h>

#include "LocalElectoralArea.h"
#include "Person.h"

MapPlotter::MapPlotter(std::vector<SmallArea*>* pAreas): _areas(pAreas) {

    BLResult err = _fontData.createFromFile("Kosugi-Regular.ttf");
    err = _fontFace.createFromData(_fontData,0);
    _font.createFromFace(_fontFace, 30);
}
#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
#endif
void write_png_file(char* filename, int pWidth, int pHeight, void **pDataPointers) {

    FILE* fp;
    fopen_s(&fp, filename, "wb");
    if (!fp) abort();

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();

    png_infop info = png_create_info_struct(png);
    if (!info) abort();

    if (setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
        png,
        info,
        pWidth, pHeight,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    png_write_image(png, (png_bytepp)pDataPointers);
    png_write_end(png, NULL);

    fclose(fp);

    png_destroy_write_struct(&png, &info);
}

void MapPlotter::PlotMap(std::string pOutputFile, boost::gregorian::date pDate, std::function<void(SmallArea&, BLContext&)> pApplyAreaStyle)
{
    double minNorthing = 0, maxNorthing = 0;
    double minEasting = 0, maxEasting = 0;
    DWORD last14dayinfectionRate = 0;
    DWORD totalInfected = 0;
    DWORD totalImmune = 0;
    DWORD totalPopulation = 0;
    for (SmallArea *area : (*_areas))
    {
    	for(auto *person: (*area->GetPeople()))
    	{
            totalPopulation++;
            if (person->GetInfection() != nullptr)
            {
                totalInfected++;
                if (person->GetInfection()->GetDaysInfected() <= 14)
                    last14dayinfectionRate++;
            }
            else if (person->IsImmune(nullptr))
                totalImmune++;
    		
    	}
        for (auto poly : (*area->GetPolygons()))
        {
            for (auto cord : *(poly.GetCoordinates()))
            {
                if (maxNorthing == 0 || maxEasting == 0)
                {
                    minNorthing = maxNorthing = cord.Northing();
                    minEasting = maxEasting = cord.Easting();
                	
                }

                if (cord.Northing() < minNorthing) minNorthing = cord.Northing();
                if (cord.Northing() > maxNorthing) maxNorthing = cord.Northing();
                if (cord.Easting() < minEasting) minEasting = cord.Easting();
                if (cord.Easting() > maxEasting) maxEasting = cord.Easting();
            }

        }
    }


    auto scale = 250;
    auto width = (maxEasting - minEasting) / scale;
    auto height = (maxNorthing - minNorthing) / scale;
    BLImage img(static_cast<int>(width), static_cast<int>(height), BL_FORMAT_PRGB32);
    BLContext ctx(img);
    ctx.setCompOp(BL_COMP_OP_SRC_COPY);
    ctx.fillAll();
    BLRgba32 color(245, 193, 137);

    ctx.setFillStyle(color);
    ctx.fillRect(0, 0, width, height);


    for (auto area : (*_areas))
    {
        for (auto poly : *(area->GetPolygons()))
        {
           // BLPath path;
            BLArray<BLPoint> coords;
        	
            auto foundBad = false;
            for (auto cord : *(poly.GetCoordinates()))
            {
                if ((cord.Easting() - minEasting) / scale < 100)
                    foundBad = true;
            	coords.append(BLPoint((cord.Easting() - minEasting) / scale, height - (cord.Northing() - minNorthing) / scale));
            }

            if (!foundBad) {
                
                ctx.setCompOp(BL_COMP_OP_SRC_OVER);
                pApplyAreaStyle(*area, ctx);
                
                ctx.fillPolygon(coords.view());
            }
        }
    }


    std::string infectedText = "Total Infected On Day " + std::to_string(totalInfected);
    auto per100krate = (double)last14dayinfectionRate / (static_cast<double>(totalPopulation) / 100000);
    std::string rateText = "National 14 Per 100k rate on "+ std::to_string(pDate.day())+"/"+ std::to_string(pDate.month())+"/"+ std::to_string(pDate.year())+" is " + std::to_string(static_cast<int>(per100krate));
    std::string immuneText = "Total Recovered Or Dead = " + std::to_string(totalImmune);
	
    ctx.fillUtf8Text(BLPoint(5, 35), _font, rateText.c_str());
    ctx.fillUtf8Text(BLPoint(5, 70), _font, infectedText.c_str());
    ctx.fillUtf8Text(BLPoint(5, 100), _font, immuneText.c_str());
    ctx.end();
    BLImageData data;
    img.getData(&data);

    auto rows = static_cast<void**>(malloc(sizeof(void*) * data.size.h));
    auto dataPointer = (char *)data.pixelData;
    for (auto i = 0; i < data.size.h; i++, dataPointer += data.stride)
        rows[i] = dataPointer;
    write_png_file(const_cast<char*>(pOutputFile.c_str()), static_cast<int>(width), static_cast<int>(height), rows);
}
