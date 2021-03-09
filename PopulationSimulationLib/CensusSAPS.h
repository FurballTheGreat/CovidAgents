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
#pragma once

#include "Common.h"

typedef struct {
    DWORD Age0Males;
    DWORD Age1Males;
    DWORD Age2Males;
    DWORD Age3Males;
    DWORD Age4Males;
    DWORD Age5Males;
    DWORD Age6Males;
    DWORD Age7Males;
    DWORD Age8Males;
    DWORD Age9Males;
    DWORD Age10Males;
    DWORD Age11Males;
    DWORD Age12Males;
    DWORD Age13Males;
    DWORD Age14Males;
    DWORD Age15Males;
    DWORD Age16Males;
    DWORD Age17Males;
    DWORD Age18Males;
    DWORD Age19Males;
    DWORD Age20To24Males;
    DWORD Age25To29Males;
    DWORD Age30To34Males;
    DWORD Age35To39Males;
    DWORD Age40To44Males;
    DWORD Age45To49Males;
    DWORD Age50To54Males;
    DWORD Age55To59Males;
    DWORD Age60To64Males;
    DWORD Age65To69Males;
    DWORD Age70To74Males;
    DWORD Age75To79Males;
    DWORD Age80To84Males;
    DWORD Age85AndOverMales;
    DWORD TotalMales;
    DWORD Age0Females;
    DWORD Age1Females;
    DWORD Age2Females;
    DWORD Age3Females;
    DWORD Age4Females;
    DWORD Age5Females;
    DWORD Age6Females;
    DWORD Age7Females;
    DWORD Age8Females;
    DWORD Age9Females;
    DWORD Age10Females;
    DWORD Age11Females;
    DWORD Age12Females;
    DWORD Age13Females;
    DWORD Age14Females;
    DWORD Age15Females;
    DWORD Age16Females;
    DWORD Age17Females;
    DWORD Age18Females;
    DWORD Age19Females;
    DWORD Age20To24Females;
    DWORD Age25To29Females;
    DWORD Age30To34Females;
    DWORD Age35To39Females;
    DWORD Age40To44Females;
    DWORD Age45To49Females;
    DWORD Age50To54Females;
    DWORD Age55To59Females;
    DWORD Age60To64Females;
    DWORD Age65To69Females;
    DWORD Age70To74Females;
    DWORD Age75To79Females;
    DWORD Age80To84Females;
    DWORD Age85AndOverFemales;
    DWORD TotalFemales;
    DWORD Age0Total;
    DWORD Age1Total;
    DWORD Age2Total;
    DWORD Age3Total;
    DWORD Age4Total;
    DWORD Age5Total;
    DWORD Age6Total;
    DWORD Age7Total;
    DWORD Age8Total;
    DWORD Age9Total;
    DWORD Age10Total;
    DWORD Age11Total;
    DWORD Age12Total;
    DWORD Age13Total;
    DWORD Age14Total;
    DWORD Age15Total;
    DWORD Age16Total;
    DWORD Age17Total;
    DWORD Age18Total;
    DWORD Age19Total;
    DWORD Age20To24Total;
    DWORD Age25To29Total;
    DWORD Age30To34Total;
    DWORD Age35To39Total;
    DWORD Age40To44Total;
    DWORD Age45To49Total;
    DWORD Age50To54Total;
    DWORD Age55To59Total;
    DWORD Age60To64Total;
    DWORD Age65To69Total;
    DWORD Age70To74Total;
    DWORD Age75To79Total;
    DWORD Age80To84Total;
    DWORD Age85AndOverTotal;
    DWORD Total;
} ThemePopulationAged019BySexAndYearOfAgePersonsAged20YearsAndOverBySexAndAgeGroup;

typedef struct {
    DWORD SingleMales;
    DWORD MarriedInclSameSexCivilPartnershipMales;
    DWORD SeparatedMales;
    DWORD DivorcedMales;
    DWORD WidowedMales;
    DWORD TotalMales;
    DWORD SingleFemales;
    DWORD MarriedInclSameSexCivilPartnershipFemales;
    DWORD SeparatedFemales;
    DWORD DivorcedFemales;
    DWORD WidowedFemales;
    DWORD TotalFemales;
    DWORD SingleTotal;
    DWORD MarriedInclSameSexCivilPartnershipTotal;
    DWORD SeparatedTotal;
    DWORD DivorcedTotal;
    DWORD WidowedTotal;
    DWORD Total;
} ThemePopulationBySexAndMaritalStatus;

typedef struct {
    DWORD IrelandBirthplace;
    DWORD UkBirthplace;
    DWORD PolandBirthplace;
    DWORD LithuaniaBirthplace;
    DWORD OtherEu28Birthplace;
    DWORD RestOfWorldBirthplace;
    DWORD TotalBirthplace;
    DWORD IrelandNationality;
    DWORD UkNationality;
    DWORD PolandNationality;
    DWORD LithuaniaNationality;
    DWORD OtherEu28Nationality;
    DWORD RestOfWorldNationality;
    DWORD NotStatedNationality;
    DWORD TotalNationality;
} ThemeUsuallyResidentPopulationByPlaceOfBirthAndNationality;

typedef struct {
    DWORD WhiteIrish;
    DWORD WhiteIrishTraveller;
    DWORD OtherWhite;
    DWORD BlackOrBlackIrish;
    DWORD AsianOrAsianIrish;
    DWORD Other;
    DWORD NotStated;
    DWORD Total;
} ThemeUsuallyResidentPopulationByEthnicOrCulturalBackground;

typedef struct {
    DWORD SameAddress;
    DWORD ElsewhereInCounty;
    DWORD ElsewhereInIreland;
    DWORD OutsideIreland;
    DWORD Total;
} ThemeUsuallyResidentPopulationAged1YearAndOverByUsualResidence1YearBeforeCensusDay;

typedef struct {
    DWORD Catholic;
    DWORD OtherReligion;
    DWORD NoReligion;
    DWORD NotStated;
    DWORD Total;
} ThemePopulationByReligion;

typedef struct {
    DWORD Polish;
    DWORD French;
    DWORD Lithuanian;
    DWORD OtherInclNotStated;
    DWORD Total;
} ThemeSpeakersOfForeignLanguagesByLanguageSpoken;

typedef struct {
    DWORD VeryWell;
    DWORD Well;
    DWORD NotWell;
    DWORD NotAtAll;
    DWORD NotStated;
    DWORD Total;
} ThemeSpeakersOfForeignLanguagesByAbilityToSpeakEnglish;

typedef struct {
    DWORD Yes;
    DWORD No;
    DWORD NotStated;
    DWORD Total;
} ThemePopulationAged3YearsAndOverByAbilityToSpeakIrish;

typedef struct {
    DWORD DailyOnlyWithinTheEducationSystemMales;
    DWORD DailyWithinAndDailyOutsideTheEducationSystemMales;
    DWORD DailyWithinAndWeeklyOutsideTheEducationSystemMales;
    DWORD DailyWithinAndLessOftenOutsideTheEducationSystemMales;
    DWORD DailyWithinAndNeverOutsideTheEducationSystemMales;
    DWORD DailyOnlyOutsideTheEducationSystemMales;
    DWORD WeeklyOnlyOutsideTheEducationSystemMales;
    DWORD LessOftenOnlyOutsideTheEducationSystemMales;
    DWORD NeverSpeaksIrishMales;
    DWORD NotStatedMales;
    DWORD AllIrishSpeakersMales;
    DWORD DailyOnlyWithinTheEducationSystemFemales;
    DWORD DailyWithinAndDailyOutsideTheEducationSystemFemales;
    DWORD DailyWithinAndWeeklyOutsideTheEducationSystemFemales;
    DWORD DailyWithinAndLessOftenOutsideTheEducationSystemFemales;
    DWORD DailyWithinAndNeverOutsideTheEducationSystemFemales;
    DWORD DailyOnlyOutsideTheEducationSystemFemales;
    DWORD WeeklyOnlyOutsideTheEducationSystemFemales;
    DWORD LessOftenOnlyOutsideTheEducationSystemFemales;
    DWORD NeverSpeaksIrishFemales;
    DWORD NotStatedFemales;
    DWORD AllIrishSpeakersFemales;
    DWORD DailyOnlyWithinTheEducationSystemTotal;
    DWORD DailyWithinAndDailyOutsideTheEducationSystemTotal;
    DWORD DailyWithinAndWeeklyOutsideTheEducationSystemTotal;
    DWORD DailyWithinAndLessOftenOutsideTheEducationSystemTotal;
    DWORD DailyWithinAndNeverOutsideTheEducationSystemTotal;
    DWORD DailyOnlyOutsideTheEducationSystemTotal;
    DWORD WeeklyOnlyOutsideTheEducationSystemTotal;
    DWORD LessOftenOnlyOutsideTheEducationSystemTotal;
    DWORD NeverSpeaksIrishTotal;
    DWORD NotStatedTotal;
    DWORD AllIrishSpeakersTotal;
} ThemeIrishSpeakersAged3YearsAndOverByFrequencyOfSpeakingIrish;

typedef struct {
    DWORD TwoPersonsNoOfFamilies;
    DWORD ThreePersonsNoOfFamilies;
    DWORD FourPersonsNoOfFamilies;
    DWORD FivePersonsNoOfFamilies;
    DWORD SixOrMorePersonsNoOfFamilies;
    DWORD TotalNoOfFamilies;
    DWORD TwoPersonsNoOfPersons;
    DWORD ThreePersonsNoOfPersons;
    DWORD FourPersonsNoOfPersons;
    DWORD FivePersonsNoOfPersons;
    DWORD SixOrMorePersonsNoOfPersons;
    DWORD TotalNoOfPersons;
    DWORD TwoPersonsNoOfChildren;
    DWORD ThreePersonsNoOfChildren;
    DWORD FourPersonsNoOfChildren;
    DWORD FivePersonsNoOfChildren;
    DWORD SixOrMorePersonsNoOfChildren;
    DWORD TotalNoOfChildren;
} ThemeFamiliesFamilyMembersAndChildrenInFamiliesBySizeOfFamily;



typedef struct {
    DWORD FamiliesWith1ChildAllChildrenAgedUnder15;
    DWORD FamiliesWith2ChildrenAllChildrenAgedUnder15;
    DWORD FamilesWith3ChildrenAllChildrenAgedUnder15;
    DWORD FamiliesWith4ChildrenAllChildrenAgedUnder15;
    DWORD FamiliesWith5OrMoreChildrenAllChildrenAgedUnder15;
    DWORD TotalFamiliesAllChildrenAgedUnder15;
    DWORD FamiliesWith1ChildAllChildrenAged15AndOver;
    DWORD FamiliesWith2ChildrenAllChildrenAged15AndOver;
    DWORD FamilesWith3ChildrenAllChildrenAged15AndOver;
    DWORD FamiliesWith4ChildrenAllChildrenAged15AndOver;
    DWORD FamiliesWith5OrMoreChildrenAllChildrenAged15AndOver;
    DWORD TotalFamiliesAllChildrenAged15AndOver;
    DWORD FamiliesWith2ChildrenAllChildrenAgedBothUnder15And15AndOver;
    DWORD FamilesWith3ChildrenAllChildrenAgedBothUnder15And15AndOver;
    DWORD FamiliesWith4ChildrenAllChildrenAgedBothUnder15And15AndOver;
    DWORD FamiliesWith5OrMoreChildrenAllChildrenAgedBothUnder15And15AndOver;
    DWORD TotalFamiliesAllChildrenAgedBothUnder15And15AndOver;
    DWORD FamiliesWithoutChildrenTotal;
    DWORD FamiliesWith1ChildTotal;
    DWORD FamiliesWith2ChildrenTotal;
    DWORD FamilesWith3ChildrenTotal;
    DWORD FamiliesWith4ChildrenTotal;
    DWORD FamiliesWith5OrMoreChildrenTotal;
    DWORD TotalFamiliesTotal;
} ThemeFamilyUnitsWithChildrenBySizeAndAgeOfChildren;

typedef struct {
    DWORD CouplesWithAllChildrenAgedUnder15NoOfFamilies;
    DWORD CouplesWithAllChildrenAged15AndOverNoOfFamilies;
    DWORD CouplesWithAllChildrenAgedBothUnder15And15AndOverNoOfFamilies;
    DWORD TotalCouplesWithChildrenNoOfFamilies;
    DWORD OneParentFamilyMotherWithAllChildrenAgedUnder15NoOfFamilies;
    DWORD OneParentFamilyMotherWithAllChildrenAged15AndOverNoOfFamilies;
    DWORD OneParentFamilyMotherWithAllChildrenAgedBothUnder15And15AndOverNoOfFamilies;
    DWORD TotalOneParentFamilyMotherWithChildrenNoOfFamilies;
    DWORD OneParentFamilyFatherWithAllChildrenAgedUnder15NoOfFamilies;
    DWORD OneParentFamilyFatherWithAllChildrenAged15AndOverNoOfFamilies;
    DWORD OneParentFamilyFatherWithAllChildrenAgedBothUnder15And15AndOverNoOfFamilies;
    DWORD TotalOneParentFamilyFatherWithChildrenNoOfFamilies;
    DWORD CouplesWithAllChildrenAgedUnder15NoOfChildren;
    DWORD CouplesWithAllChildrenAged15AndOverNoOfChildren;
    DWORD CouplesWithAllChildrenAgedBothUnder15And15AndOverNoOfChildren;
    DWORD TotalCouplesWithChildrenNoOfChildren;
    DWORD OneParentFamilyMotherWithAllChildrenAgedUnder15NoOfChildren;
    DWORD OneParentFamilyMotherWithAllChildrenAged15AndOverNoOfChildren;
    DWORD OneParentFamilyMotherWithAllChildrenAgedBothUnder15And15AndOverNoOfChildren;
    DWORD TotalOneParentFamilyMotherWithChildrenNoOfChildren;
    DWORD OneParentFamilyFatherWithAllChildrenAgedUnder15NoOfChildren;
    DWORD OneParentFamilyFatherWithAllChildrenAged15AndOverNoOfChildren;
    DWORD OneParentFamilyFatherWithAllChildrenAgedBothUnder15And15AndOverNoOfChildren;
    DWORD TotalOneParentFamilyFatherWithChildrenNoOfChildren;
} ThemeFamilyUnitsWithChildrenByTypeOfFamilyAndAgeOfChildren;

typedef struct {
    DWORD FamiliesWithYoungestChildAged0To4NoOfFamilies;
    DWORD FamiliesWithYoungestChildAged5To9NoOfFamilies;
    DWORD FamiliesWithYoungestChildAged10To14NoOfFamilies;
    DWORD FamiliesWithYoungestChildAged15To19NoOfFamilies;
    DWORD FamiliesWithYoungestChildAged20AndOverNoOfFamilies;
    DWORD TotalNoOfFamilies;
    DWORD FamiliesWithYoungestChildAged0To4NoOfPersons;
    DWORD FamiliesWithYoungestChildAged5To9NoOfPersons;
    DWORD FamiliesWithYoungestChildAged10To14NoOfPersons;
    DWORD FamiliesWithYoungestChildAged15To19NoOfPersons;
    DWORD FamiliesWithYoungestChildAged20AndOverNoOfPersons;
    DWORD TotalNoOfPersons;
} ThemeFamiliesByAgeOfYoungestChild;

typedef struct {
    DWORD PrefamilyNoOfFamilies;
    DWORD EmptyNestNoOfFamilies;
    DWORD RetiredNoOfFamilies;
    DWORD PreschoolNoOfFamilies;
    DWORD EarlySchoolNoOfFamilies;
    DWORD PreadolescentNoOfFamilies;
    DWORD AdolescentNoOfFamilies;
    DWORD AdultNoOfFamilies;
    DWORD TotalNoOfFamilies;
    DWORD PrefamilyNoOfPersons;
    DWORD EmptyNestNoOfPersons;
    DWORD RetiredNoOfPersons;
    DWORD PreschoolNoOfPersons;
    DWORD EarlySchoolNoOfPersons;
    DWORD PreadolescentNoOfPersons;
    DWORD AdolescentNoOfPersons;
    DWORD AdultNoOfPersons;
    DWORD TotalNoOfPersons;
} ThemeFamiliesByFamilyCycle;

typedef struct {
    DWORD ZeroChildrenBorn;
    DWORD OneChildBorn;
    DWORD TwoChildrenBorn;
    DWORD ThreeChildrenBorn;
    DWORD FourOrMoreChildrenBorn;
    DWORD Total;
} ThemeFemalesAged20YearsAndOverByNumberOfChildrenBorn;
enum class PrivateHouseholdsType
{
    OnePersonHouseholds = 0,
	MarriedCoupleHouseholds = 1,
    CohabitingCoupleHouseholds =2,
	MarriedCoupleWithChildrenHouseholds=3,
    CohabitingCoupleWithChildrenHouseholds =4,
	OneParentFamilyFatherWithChildrenHouseholds = 5,
	OneParentFamilyMotherAndChildrenHouseholds = 6,
	CoupleAndOthersHouseholds = 7,
	CoupleWithChildrenAndOthersHouseholds = 8,
	OneParentFamilyFatherWithChildrenAndOthersHouseholds = 9,
	OneParentFamilyMotherWithChildrenAndOthersHouseholds = 10,
	TwoOrMoreFamilyUnitsHouseholds = 11,
	NonfamilyHouseholdsAndRelationsHouseholds = 12,
	TwoOrMoreNonrelatedPersonsHouseholds = 13
}; 
typedef struct {
    DWORD NoOfHouseholds[14];
    DWORD TotalHouseholdsNoOfHouseholds;
    DWORD NoOfPersons[14];
    DWORD TotalHouseholdsNoOfPersons;
} ThemePrivateHouseholdsByType;

typedef struct {
    DWORD NoOfHouseholds[8];    
    DWORD TotalHouseholdsNoOfHouseholds;
    DWORD NoOfPersons[8];    
    DWORD TotalHouseholdsNoOfPersons;
} ThemePrivateHouseholdsBySize;

typedef struct {
    DWORD HousebungalowNoOfHouseholds;
    DWORD FlatapartmentNoOfHouseholds;
    DWORD BedsitNoOfHouseholds;
    DWORD CaravanmobileHomeNoOfHouseholds;
    DWORD NotStatedNoOfHouseholds;
    DWORD TotalNoOfHouseholds;
    DWORD HousebungalowNoOfPersons;
    DWORD FlatapartmentNoOfPersons;
    DWORD BedsitNoOfPersons;
    DWORD CaravanmobileHomeNoOfPersons;
    DWORD NotStatedNoOfPersons;
    DWORD TotalNoOfPersons;
} ThemePrivateHouseholdsByTypeOfAccommodation;

typedef struct {
    DWORD Pre1919NoOfHouseholds;
    DWORD R1919To1945NoOfHouseholds;
    DWORD R1946To1960NoOfHouseholds;
    DWORD R1961To1970NoOfHouseholds;
    DWORD R1971To1980NoOfHouseholds;
    DWORD R1981To1990NoOfHouseholds;
    DWORD R1991To2000NoOfHouseholds;
    DWORD R2001To2010NoOfHouseholds;
    DWORD R2011OrLaterNoOfHouseholds;
    DWORD NotStatedNoOfHouseholds;
    DWORD TotalNoOfHouseholds;
    DWORD Pre1919NoOfPersons;
    DWORD R1919To1945NoOfPersons;
    DWORD R1946To1960NoOfPersons;
    DWORD R1961To1970NoOfPersons;
    DWORD R1971To1980NoOfPersons;
    DWORD R1981To1990NoOfPersons;
    DWORD R1991To2000NoOfPersons;
    DWORD R2001To2010NoOfPersons;
    DWORD R2011OrLaterNoOfPersons;
    DWORD NotStatedNoOfPersons;
    DWORD TotalNoOfPersons;
} ThemePermanentPrivateHouseholdsByYearBuilt;

typedef struct {
    DWORD OwnedWithMortgageOrLoanNoOfHouseholds;
    DWORD OwnedOutrightNoOfHouseholds;
    DWORD RentedFromPrivateLandlordNoOfHouseholds;
    DWORD RentedFromLocalAuthorityNoOfHouseholds;
    DWORD RentedFromVoluntarycooperativeHousingBodyNoOfHouseholds;
    DWORD OccupiedFreeOfRentNoOfHouseholds;
    DWORD NotStatedNoOfHouseholds;
    DWORD TotalNoOfHouseholds;
    DWORD OwnedWithMortgageOrLoanNoOfPersons;
    DWORD OwnedOutrightNoOfPersons;
    DWORD RentedFromPrivateLandlordNoOfPersons;
    DWORD RentedFromLocalAuthorityNoOfPersons;
    DWORD RentedFromVoluntarycooperativeHousingBodyNoOfPersons;
    DWORD OccupiedFreeOfRentNoOfPersons;
    DWORD NotStatedNoOfPersons;
    DWORD TotalNoOfPersons;
} ThemePermanentPrivateHouseholdsByTypeOfOccupancy;

typedef struct {
    DWORD OneRoomNoOfHouseholds;
    DWORD TwoRoomsNoOfHouseholds;
    DWORD ThreeRoomsNoOfHouseholds;
    DWORD FourRoomsNoOfHouseholds;
    DWORD FiveRoomsNoOfHouseholds;
    DWORD SixRoomsNoOfHouseholds;
    DWORD SevenRoomsNoOfHouseholds;
    DWORD EightOrMoreRoomsNoOfHouseholds;
    DWORD NotStatedNoOfHouseholds;
    DWORD TotalNoOfHouseholds;
    DWORD OneRoomNoOfPersons;
    DWORD TwoRoomsNoOfPersons;
    DWORD ThreeRoomsNoOfPersons;
    DWORD FourRoomsNoOfPersons;
    DWORD FiveRoomsNoOfPersons;
    DWORD SixRoomsNoOfPersons;
    DWORD SevenRoomsNoOfPersons;
    DWORD EightOrMoreRoomsNoOfPersons;
    DWORD NotStatedNoOfPersons;
    DWORD TotalNoOfPersons;
} ThemePermanentPrivateHouseholdsByNumberOfRooms;

typedef struct {
    DWORD NoCentralHeating;
    DWORD Oil;
    DWORD NaturalGas;
    DWORD Electricity;
    DWORD CoalInclAnthracite;
    DWORD PeatInclTurf;
    DWORD LiquidPetroleumGasLpg;
    DWORD WoodInclWoodPellets;
    DWORD Other;
    DWORD NotStated;
    DWORD Total;
} ThemePermanentPrivateHouseholdsByCentralHeating;

typedef struct {
    DWORD PublicMain;
    DWORD GroupSchemeWithPublicSource;
    DWORD GroupSchemeWithPrivateSource;
    DWORD OtherPrivateSource;
    DWORD None;
    DWORD NotStated;
    DWORD Total;
} ThemePermanentPrivateHouseholdsByWaterSupply;

typedef struct {
    DWORD PublicScheme;
    DWORD IndividualSepticTank;
    DWORD OtherIndividualTreatment;
    DWORD Other;
    DWORD NoSewerageFacility;
    DWORD NotStated;
    DWORD Total;
} ThemePermanentPrivateHouseholdsBySewerageFacility;

typedef struct {
    DWORD Occupied;
    DWORD TemporarilyAbsent;
    DWORD UnoccupiedHolidayHomes;
    DWORD OtherVacantDwellings;
    DWORD Total;
} ThemeOccupancyStatusOfPermanentDwellingsOnCensusNight;

typedef struct {
    DWORD NumberOfEstablishments;
    DWORD NumberOfPersons;
} ThemePersonsInCommunalEstablishments;

typedef struct {
    DWORD AtWorkMales;
    DWORD LookingForFirstRegularJobMales;
    DWORD UnemployedHavingLostOrGivenUpPreviousJobMales;
    DWORD StudentMales;
    DWORD LookingAfterHomefamilyMales;
    DWORD RetiredMales;
    DWORD UnableToWorkDueToPermanentSicknessOrDisabilityMales;
    DWORD OtherMales;
    DWORD TotalMales;
    DWORD AtWorkFemales;
    DWORD LookingForFirstRegularJobFemales;
    DWORD UnemployedHavingLostOrGivenUpPreviousJobFemales;
    DWORD StudentFemales;
    DWORD LookingAfterHomefamilyFemales;
    DWORD RetiredFemales;
    DWORD UnableToWorkDueToPermanentSicknessOrDisabilityFemales;
    DWORD OtherFemales;
    DWORD TotalFemales;
    DWORD AtWorkTotal;
    DWORD LookingForFirstRegularJobTotal;
    DWORD UnemployedHavingLostOrGivenUpPreviousJobTotal;
    DWORD StudentTotal;
    DWORD LookingAfterHomefamilyTotal;
    DWORD RetiredTotal;
    DWORD UnableToWorkDueToPermanentSicknessOrDisabilityTotal;
    DWORD OtherTotal;
    DWORD Total;
} ThemePopulationAged15YearsAndOverByPrincipalEconomicStatusAndSex;

typedef struct {
    DWORD ProfessionalWorkersMales;
    DWORD ManagerialAndTechnicalMales;
    DWORD NonmanualMales;
    DWORD SkilledManualMales;
    DWORD SemiskilledMales;
    DWORD UnskilledMales;
    DWORD AllOthersGainfullyOccupiedAndUnknownMales;
    DWORD TotalMales;
    DWORD ProfessionalWorkersFemales;
    DWORD ManagerialAndTechnicalFemales;
    DWORD NonmanualFemales;
    DWORD SkilledManualFemales;
    DWORD SemiskilledFemales;
    DWORD UnskilledFemales;
    DWORD AllOthersGainfullyOccupiedAndUnknownFemales;
    DWORD TotalFemales;
    DWORD ProfessionalWorkersTotal;
    DWORD ManagerialAndTechnicalTotal;
    DWORD NonmanualTotal;
    DWORD SkilledManualTotal;
    DWORD SemiskilledTotal;
    DWORD UnskilledTotal;
    DWORD AllOthersGainfullyOccupiedAndUnknownTotal;
    DWORD Total;
} ThemePopulationBySexAndSocialClass;

typedef struct {
    DWORD AEmployersAndManagersNoOfHouseholds;
    DWORD BHigherProfessionalNoOfHouseholds;
    DWORD CLowerProfessionalNoOfHouseholds;
    DWORD DNonmanualNoOfHouseholds;
    DWORD EManualSkilledNoOfHouseholds;
    DWORD FSemiskilledNoOfHouseholds;
    DWORD GUnskilledNoOfHouseholds;
    DWORD HOwnAccountWorkersNoOfHouseholds;
    DWORD IFarmersNoOfHouseholds;
    DWORD JAgriculturalWorkersNoOfHouseholds;
    DWORD ZAllOthersGainfullyOccupiedAndUnknownNoOfHouseholds;
    DWORD TotalNoOfHouseholds;
    DWORD AEmployersAndManagersNoOfPersons;
    DWORD BHigherProfessionalNoOfPersons;
    DWORD CLowerProfessionalNoOfPersons;
    DWORD DNonmanualNoOfPersons;
    DWORD EManualSkilledNoOfPersons;
    DWORD FSemiskilledNoOfPersons;
    DWORD GUnskilledNoOfPersons;
    DWORD HOwnAccountWorkersNoOfPersons;
    DWORD IFarmersNoOfPersons;
    DWORD JAgriculturalWorkersNoOfPersons;
    DWORD ZAllOthersGainfullyOccupiedAndUnknownNoOfPersons;
    DWORD TotalNoOfPersons;
} ThemePersonsInPrivateHouseholdsBySocioeconomicGroupOfReferencePerson;

typedef struct {
    DWORD AgeUnder15Males;
    DWORD Age15Males;
    DWORD Age16Males;
    DWORD Age17Males;
    DWORD Age18Males;
    DWORD Age19Males;
    DWORD Age20Males;
    DWORD Age21AndOverMales;
    DWORD NotStatedMales;
    DWORD TotalMales;
    DWORD AgeUnder15Females;
    DWORD Age15Females;
    DWORD Age16Females;
    DWORD Age17Females;
    DWORD Age18Females;
    DWORD Age19Females;
    DWORD Age20Females;
    DWORD Age21AndOverFemales;
    DWORD NotStatedFemales;
    DWORD TotalFemales;
    DWORD AgeUnder15Total;
    DWORD Age15Total;
    DWORD Age16Total;
    DWORD Age17Total;
    DWORD Age18Total;
    DWORD Age19Total;
    DWORD Age20Total;
    DWORD Age21AndOverTotal;
    DWORD NotStatedTotal;
    DWORD Total;
} ThemePopulationAged15YearsAndOverByAgeEducationCeased;

typedef struct {
    DWORD StillAtSchoolOrCollegeMales;
    DWORD OtherMales;
    DWORD StillAtSchoolOrCollegeFemales;
    DWORD OtherFemales;
    DWORD StillAtSchoolOrCollegeTotal;
    DWORD OtherTotal;
} ThemePopulationAged15YearsAndOverWhoseEducationHasNotCeased;

typedef struct {
    DWORD EducationAndTeacherTrainingMales;
    DWORD ArtsMales;
    DWORD HumanitiesMales;
    DWORD SocialSciencesBusinessAndLawMales;
    DWORD ScienceMathematicsAndComputingMales;
    DWORD EngineeringManufacturingAndConstructionMales;
    DWORD AgricultureAndVeterinaryMales;
    DWORD HealthAndWelfareMales;
    DWORD ServicesMales;
    DWORD OtherSubjectsMales;
    DWORD NotStatedMales;
    DWORD TotalMales;
    DWORD EducationAndTeacherTrainingFemales;
    DWORD ArtsFemales;
    DWORD HumanitiesFemales;
    DWORD SocialSciencesBusinessAndLawFemales;
    DWORD ScienceMathematicsAndComputingFemales;
    DWORD EngineeringManufacturingAndConstructionFemales;
    DWORD AgricultureAndVeterinaryFemales;
    DWORD HealthAndWelfareFemales;
    DWORD ServicesFemales;
    DWORD OtherSubjectsFemales;
    DWORD NotStatedFemales;
    DWORD TotalFemales;
    DWORD EducationAndTeacherTrainingTotal;
    DWORD ArtsTotal;
    DWORD HumanitiesTotal;
    DWORD SocialSciencesBusinessAndLawTotal;
    DWORD ScienceMathematicsAndComputingTotal;
    DWORD EngineeringManufacturingAndConstructionTotal;
    DWORD AgricultureAndVeterinaryTotal;
    DWORD HealthAndWelfareTotal;
    DWORD ServicesTotal;
    DWORD OtherSubjectsTotal;
    DWORD NotStatedTotal;
    DWORD Total;
} ThemePopulationAged15YearsAndOverByFieldOfStudy;

typedef struct {
    DWORD NoFormalEducationMales;
    DWORD PrimaryEducationMales;
    DWORD LowerSecondaryMales;
    DWORD UpperSecondaryMales;
    DWORD TechnicalOrVocationalQualificationMales;
    DWORD AdvancedCertificatecompletedApprenticeshipMales;
    DWORD HigherCertificateMales;
    DWORD OrdinaryBachelorDegreeOrNationalDiplomaMales;
    DWORD HonoursBachelorDegreeProfessionalQualificationOrBothMales;
    DWORD PostgraduateDiplomaOrDegreeMales;
    DWORD DoctoratephdOrHigherMales;
    DWORD NotStatedMales;
    DWORD TotalMales;
    DWORD NoFormalEducationFemales;
    DWORD PrimaryEducationFemales;
    DWORD LowerSecondaryFemales;
    DWORD UpperSecondaryFemales;
    DWORD TechnicalOrVocationalQualificationFemales;
    DWORD AdvancedCertificatecompletedApprenticeshipFemales;
    DWORD HigherCertificateFemales;
    DWORD OrdinaryBachelorDegreeOrNationalDiplomaFemales;
    DWORD HonoursBachelorDegreeProfessionalQualificationOrBothFemales;
    DWORD PostgraduateDiplomaOrDegreeFemales;
    DWORD DoctoratephdOrHigherFemales;
    DWORD NotStatedFemales;
    DWORD TotalFemales;
    DWORD NoFormalEducationTotal;
    DWORD PrimaryEducationTotal;
    DWORD LowerSecondaryTotal;
    DWORD UpperSecondaryTotal;
    DWORD TechnicalOrVocationalQualificationTotal;
    DWORD AdvancedCertificatecompletedApprenticeshipTotal;
    DWORD HigherCertificateTotal;
    DWORD OrdinaryBachelorDegreeOrNationalDiplomaTotal;
    DWORD HonoursBachelorDegreeProfessionalQualificationOrBothTotal;
    DWORD PostgraduateDiplomaOrDegreeTotal;
    DWORD DoctoratephdOrHigherTotal;
    DWORD NotStatedTotal;
    DWORD Total;
} ThemePopulationAged15YearsAndOverBySexAndHighestLevelOfEducationCompleted;

typedef struct {
    DWORD OnFootWork;
    DWORD BicycleWork;
    DWORD BusMinibusOrCoachWork;
    DWORD TrainDartOrLuasWork;
    DWORD MotorcycleOrScooterWork;
    DWORD CarDriverWork;
    DWORD CarPassengerWork;
    DWORD VanWork;
    DWORD OtherInclLorryWork;
    DWORD WorkMainlyAtOrFromHomeWork;
    DWORD NotStatedWork;
    DWORD TotalWork;
    DWORD OnFootSchoolOrCollege;
    DWORD BicycleSchoolOrCollege;
    DWORD BusMinibusOrCoachSchoolOrCollege;
    DWORD TrainDartOrLuasSchoolOrCollege;
    DWORD MotorcycleOrScooterSchoolOrCollege;
    DWORD CarDriverSchoolOrCollege;
    DWORD CarPassengerSchoolOrCollege;
    DWORD VanSchoolOrCollege;
    DWORD OtherInclLorrySchoolOrCollege;
    DWORD WorkMainlyAtOrFromHomeSchoolOrCollege;
    DWORD NotStatedSchoolOrCollege;
    DWORD TotalSchoolOrCollege;
    DWORD OnFootTotal;
    DWORD BicycleTotal;
    DWORD BusMinibusOrCoachTotal;
    DWORD TrainDartOrLuasTotal;
    DWORD MotorcycleOrScooterTotal;
    DWORD CarDriverTotal;
    DWORD CarPassengerTotal;
    DWORD VanTotal;
    DWORD OtherInclLorryTotal;
    DWORD WorkMainlyAtOrFromHomeTotal;
    DWORD NotStatedTotal;
    DWORD Total;
} ThemePopulationAged5YearsAndOverByMeansOfTravelToWorkSchoolOrCollege;

typedef struct {
    DWORD Before0630;
    DWORD R0630To0700;
    DWORD R0701To0730;
    DWORD R0731To0800;
    DWORD R0801To0830;
    DWORD R0831To0900;
    DWORD R0901To0930;
    DWORD After0930;
    DWORD NotStated;
    DWORD Total;
} ThemePopulationAged5YearsAndOverByTimeLeavingHomeToTravelToWorkSchoolOrCollege;

typedef struct {
    DWORD Under15Mins;
    DWORD R14HourUnder12Hour;
    DWORD R12HourUnder34Hour;
    DWORD R34HourUnder1Hour;
    DWORD OneHourUnder112Hours;
    DWORD R112HoursAndOver;
    DWORD NotStated;
    DWORD Total;
} ThemePopulationAged5YearsAndOverByJourneyTimeToWorkSchoolOrCollege;

typedef struct {
    DWORD Males;
    DWORD Females;
    DWORD Total;
} ThemePersonsWithDisabilityBySex;

typedef struct {
    DWORD Males;
    DWORD Females;
    DWORD Total;
} ThemeCarersBySex;

typedef struct {
    DWORD VeryGoodMales;
    DWORD VeryGoodFemales;
    DWORD VeryGoodTotal;
    DWORD GoodMales;
    DWORD GoodFemales;
    DWORD GoodTotal;
    DWORD FairMales;
    DWORD FairFemales;
    DWORD FairTotal;
    DWORD BadMales;
    DWORD BadFemales;
    DWORD BadTotal;
    DWORD VeryBadMales;
    DWORD VeryBadFemales;
    DWORD VeryBadTotal;
    DWORD NotStatedMales;
    DWORD NotStatedFemales;
    DWORD NotStatedTotal;
    DWORD TotalMales;
    DWORD TotalFemales;
    DWORD Total;
} ThemePopulationByGeneralHealthAndSex;

typedef struct {
    DWORD ManagersDirectorsAndSeniorOfficialsMales;
    DWORD ProfessionalOccupationsMales;
    DWORD AssociateProfessionalAndTechnicalOccupationsMales;
    DWORD AdministrativeAndSecretarialOccupationsMales;
    DWORD SkilledTradesOccupationsMales;
    DWORD CaringLeisureAndOtherServiceOccupationsMales;
    DWORD SalesAndCustomerServiceOccupationsMales;
    DWORD ProcessPlantAndMachineOperativesMales;
    DWORD ElementaryOccupationsMales;
    DWORD NotStatedMales;
    DWORD TotalMales;
    DWORD ManagersDirectorsAndSeniorOfficialsFemales;
    DWORD ProfessionalOccupationsFemales;
    DWORD AssociateProfessionalAndTechnicalOccupationsFemales;
    DWORD AdministrativeAndSecretarialOccupationsFemales;
    DWORD SkilledTradesOccupationsFemales;
    DWORD CaringLeisureAndOtherServiceOccupationsFemales;
    DWORD SalesAndCustomerServiceOccupationsFemales;
    DWORD ProcessPlantAndMachineOperativesFemales;
    DWORD ElementaryOccupationsFemales;
    DWORD NotStatedFemales;
    DWORD TotalFemales;
    DWORD ManagersDirectorsAndSeniorOfficialsTotal;
    DWORD ProfessionalOccupationsTotal;
    DWORD AssociateProfessionalAndTechnicalOccupationsTotal;
    DWORD AdministrativeAndSecretarialOccupationsTotal;
    DWORD SkilledTradesOccupationsTotal;
    DWORD CaringLeisureAndOtherServiceOccupationsTotal;
    DWORD SalesAndCustomerServiceOccupationsTotal;
    DWORD ProcessPlantAndMachineOperativesTotal;
    DWORD ElementaryOccupationsTotal;
    DWORD NotStatedTotal;
    DWORD Total;
} ThemePersonsAtWorkOrUnemployedByOccupationAndSex;

typedef struct {
    DWORD AgricultureForestryAndFishingMales;
    DWORD BuildingAndConstructionMales;
    DWORD ManufacturingIndustriesMales;
    DWORD CommerceAndTradeMales;
    DWORD TransportAndCommunicationsMales;
    DWORD PublicAdministrationMales;
    DWORD ProfessionalServicesMales;
    DWORD OtherMales;
    DWORD TotalMales;
    DWORD AgricultureForestryAndFishingFemales;
    DWORD BuildingAndConstructionFemales;
    DWORD ManufacturingIndustriesFemales;
    DWORD CommerceAndTradeFemales;
    DWORD TransportAndCommunicationsFemales;
    DWORD PublicAdministrationFemales;
    DWORD ProfessionalServicesFemales;
    DWORD OtherFemales;
    DWORD TotalFemales;
    DWORD AgricultureForestryAndFishingTotal;
    DWORD BuildingAndConstructionTotal;
    DWORD ManufacturingIndustriesTotal;
    DWORD CommerceAndTradeTotal;
    DWORD TransportAndCommunicationsTotal;
    DWORD PublicAdministrationTotal;
    DWORD ProfessionalServicesTotal;
    DWORD OtherTotal;
    DWORD Total;
} ThemePersonsAtWorkByIndustryAndSex;

typedef struct {
    DWORD NoMotorCar;
    DWORD OneMotorCar;
    DWORD TwoMotorCars;
    DWORD ThreeMotorCars;
    DWORD FourOrMoreMotorCars;
    DWORD NotStated;
    DWORD Total;
} ThemeNumberOfHouseholdsWithCars;

typedef struct {
    DWORD Yes;
    DWORD No;
    DWORD NotStated;
    DWORD Total;
} ThemeNumberOfHouseholdsWithAPersonalComputer;

typedef struct {
    DWORD Broadband;
    DWORD Other;
    DWORD No;
    DWORD NotStated;
    DWORD Total;
} ThemeNumberOfHouseholdsWithInternet;



typedef struct {
    ThemePopulationAged019BySexAndYearOfAgePersonsAged20YearsAndOverBySexAndAgeGroup PopulationAged019BySexAndYearOfAgePersonsAged20YearsAndOverBySexAndAgeGroup;
    ThemePopulationBySexAndMaritalStatus PopulationBySexAndMaritalStatus;
    ThemeUsuallyResidentPopulationByPlaceOfBirthAndNationality UsuallyResidentPopulationByPlaceOfBirthAndNationality;
    ThemeUsuallyResidentPopulationByEthnicOrCulturalBackground UsuallyResidentPopulationByEthnicOrCulturalBackground;
    ThemeUsuallyResidentPopulationAged1YearAndOverByUsualResidence1YearBeforeCensusDay UsuallyResidentPopulationAged1YearAndOverByUsualResidence1YearBeforeCensusDay;
    ThemePopulationByReligion PopulationByReligion;
    ThemeSpeakersOfForeignLanguagesByLanguageSpoken SpeakersOfForeignLanguagesByLanguageSpoken;
    ThemeSpeakersOfForeignLanguagesByAbilityToSpeakEnglish SpeakersOfForeignLanguagesByAbilityToSpeakEnglish;
    ThemePopulationAged3YearsAndOverByAbilityToSpeakIrish PopulationAged3YearsAndOverByAbilityToSpeakIrish;
    ThemeIrishSpeakersAged3YearsAndOverByFrequencyOfSpeakingIrish IrishSpeakersAged3YearsAndOverByFrequencyOfSpeakingIrish;
    ThemeFamiliesFamilyMembersAndChildrenInFamiliesBySizeOfFamily FamiliesFamilyMembersAndChildrenInFamiliesBySizeOfFamily;
    ThemeFamilyUnitsWithChildrenBySizeAndAgeOfChildren FamilyUnitsWithChildrenBySizeAndAgeOfChildren;
    ThemeFamilyUnitsWithChildrenByTypeOfFamilyAndAgeOfChildren FamilyUnitsWithChildrenByTypeOfFamilyAndAgeOfChildren;
    ThemeFamiliesByAgeOfYoungestChild FamiliesByAgeOfYoungestChild;
    ThemeFamiliesByFamilyCycle FamiliesByFamilyCycle;
    ThemeFemalesAged20YearsAndOverByNumberOfChildrenBorn FemalesAged20YearsAndOverByNumberOfChildrenBorn;
    ThemePrivateHouseholdsByType PrivateHouseholdsByType;
    ThemePrivateHouseholdsBySize PrivateHouseholdsBySize;
    ThemePrivateHouseholdsByTypeOfAccommodation PrivateHouseholdsByTypeOfAccommodation;
    ThemePermanentPrivateHouseholdsByYearBuilt PermanentPrivateHouseholdsByYearBuilt;
    ThemePermanentPrivateHouseholdsByTypeOfOccupancy PermanentPrivateHouseholdsByTypeOfOccupancy;
    ThemePermanentPrivateHouseholdsByNumberOfRooms PermanentPrivateHouseholdsByNumberOfRooms;
    ThemePermanentPrivateHouseholdsByCentralHeating PermanentPrivateHouseholdsByCentralHeating;
    ThemePermanentPrivateHouseholdsByWaterSupply PermanentPrivateHouseholdsByWaterSupply;
    ThemePermanentPrivateHouseholdsBySewerageFacility PermanentPrivateHouseholdsBySewerageFacility;
    ThemeOccupancyStatusOfPermanentDwellingsOnCensusNight OccupancyStatusOfPermanentDwellingsOnCensusNight;
    ThemePersonsInCommunalEstablishments PersonsInCommunalEstablishments;
    ThemePopulationAged15YearsAndOverByPrincipalEconomicStatusAndSex PopulationAged15YearsAndOverByPrincipalEconomicStatusAndSex;
    ThemePopulationBySexAndSocialClass PopulationBySexAndSocialClass;
    ThemePersonsInPrivateHouseholdsBySocioeconomicGroupOfReferencePerson PersonsInPrivateHouseholdsBySocioeconomicGroupOfReferencePerson;
    ThemePopulationAged15YearsAndOverByAgeEducationCeased PopulationAged15YearsAndOverByAgeEducationCeased;
    ThemePopulationAged15YearsAndOverWhoseEducationHasNotCeased PopulationAged15YearsAndOverWhoseEducationHasNotCeased;
    ThemePopulationAged15YearsAndOverByFieldOfStudy PopulationAged15YearsAndOverByFieldOfStudy;
    ThemePopulationAged15YearsAndOverBySexAndHighestLevelOfEducationCompleted PopulationAged15YearsAndOverBySexAndHighestLevelOfEducationCompleted;
    ThemePopulationAged5YearsAndOverByMeansOfTravelToWorkSchoolOrCollege PopulationAged5YearsAndOverByMeansOfTravelToWorkSchoolOrCollege;
    ThemePopulationAged5YearsAndOverByTimeLeavingHomeToTravelToWorkSchoolOrCollege PopulationAged5YearsAndOverByTimeLeavingHomeToTravelToWorkSchoolOrCollege;
    ThemePopulationAged5YearsAndOverByJourneyTimeToWorkSchoolOrCollege PopulationAged5YearsAndOverByJourneyTimeToWorkSchoolOrCollege;
    ThemePersonsWithDisabilityBySex PersonsWithDisabilityBySex;
    ThemeCarersBySex CarersBySex;
    ThemePopulationByGeneralHealthAndSex PopulationByGeneralHealthAndSex;
    ThemePersonsAtWorkOrUnemployedByOccupationAndSex PersonsAtWorkOrUnemployedByOccupationAndSex;
    ThemePersonsAtWorkByIndustryAndSex PersonsAtWorkByIndustryAndSex;
    ThemeNumberOfHouseholdsWithCars NumberOfHouseholdsWithCars;
    ThemeNumberOfHouseholdsWithAPersonalComputer NumberOfHouseholdsWithAPersonalComputer;
    ThemeNumberOfHouseholdsWithInternet NumberOfHouseholdsWithInternet;
} SmallPopulationAreaDefinition;


