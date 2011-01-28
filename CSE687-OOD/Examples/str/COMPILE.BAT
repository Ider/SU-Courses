:compile.bat
  cl /GX /FetestStub.exe /DTEST_STR str.cpp
  cl /GX /FeuseStr.exe useStr.cpp str.cpp