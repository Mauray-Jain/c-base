#include "constants.h"
#include "context.h"

OperatingSystem operating_system_from_context(void){
  OperatingSystem result = OperatingSystem_Null;
#if defined (OS_WINDOWS)
  result = OperatingSystem_Windows;
#elif defined (OS_LINUX)
  result = OperatingSystem_Linux;
#elif defined (OS_MAC)
  result = OperatingSystem_Mac;
#endif
  return result;
}

Architecture architecture_from_context(void){
  Architecture result = Architecture_Null;
#if defined (ARCH_X64)
  result = Architecture_X64;
#elif defined (ARCH_X86)
  result = Architecture_X86;
#elif defined (ARCH_ARM)
  result = Architecture_Arm;
#elif defined (ARCH_ARM64)
  result = Architecture_Arm64;
#endif
  return(result);
}

char* string_from_operating_system(OperatingSystem os){
  char *result = "(null)";
  switch (os){
    case OperatingSystem_Windows:
			result = "windows";
			break;
    case OperatingSystem_Linux:
			result = "linux";
			break;
    case OperatingSystem_Mac:
			result = "mac";
			break;
		default:
			break;
  }
  return result;
}

char* string_from_architecture(Architecture arch){
  char *result = "(null)";
  switch (arch){
    case Architecture_X64:
			result = "x64";
			break;
    case Architecture_X86:
			result = "x86";
			break;
    case Architecture_Arm:
			result = "arm";
			break;
    case Architecture_Arm64:
			result = "armm64";
			break;
		default:
			break;
  }
  return result;
}

char* string_from_month(Month month){
  char *result = "(null)";
  switch (month){
    case Month_Jan:
			result = "jan";
			break;
    case Month_Feb:
			result = "feb";
			break;
    case Month_Mar:
			result = "mar";
			break;
    case Month_Apr:
			result = "apr";
			break;
    case Month_May:
			result = "may";
			break;
    case Month_Jun:
			result = "jun";
			break;
    case Month_Jul:
			result = "jul";
			break;
    case Month_Aug:
			result = "aug";
			break;
    case Month_Sep:
			result = "sep";
			break;
    case Month_Oct:
			result = "oct";
			break;
    case Month_Nov:
			result = "nov";
			break;
    case Month_Dec:
			result = "dec";
			break;
  }
  return result;
}

char* string_from_day_of_week(DayOfWeek day_of_week){
  char *result = "(null)";
  switch (day_of_week){
    case DayOfWeek_Sunday:
			result = "sunday";
			break;
    case DayOfWeek_Monday:
			result = "monday";
			break;
    case DayOfWeek_Tuesday:
			result = "tuesday";
			break;
    case DayOfWeek_Wednesday:
			result = "wednesday";
			break;
    case DayOfWeek_Thursday:
			result = "thursday";
			break;
    case DayOfWeek_Friday:
			result = "friday";
			break;
    case DayOfWeek_Saturday:
			result = "saturday";
			break;
  }
  return result;
}
