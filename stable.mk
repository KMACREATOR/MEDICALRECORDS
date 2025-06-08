##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=stable
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=C:/Users/MK/Documents/courseproject
ProjectPath            :=C:/Users/MK/Documents/courseproject/stable
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/stable
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=MK
Date                   :=6/8/2025
CodeLitePath           :="C:/Program Files/CodeLite"
MakeDirCommand         :=mkdir
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=C:/Users/MK/Documents/courseproject/build-$(WorkspaceConfiguration)/bin
OutputFile             :=..\build-$(WorkspaceConfiguration)\bin\$(ProjectName).exe
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -gdwarf-2 -O0 -Wall $(Preprocessors)
CFLAGS   :=  -gdwarf-2 -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/Student.cpp$(ObjectSuffix) $(IntermediateDirectory)/MedicalRecord.cpp$(ObjectSuffix) $(IntermediateDirectory)/Time.cpp$(ObjectSuffix) $(IntermediateDirectory)/MedicalRecordList.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@if not exist "$(OutputDirectory)" $(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory)/.d:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Student.cpp$(ObjectSuffix): Student.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/MK/Documents/courseproject/stable/Student.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Student.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Student.cpp$(PreprocessSuffix): Student.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Student.cpp$(PreprocessSuffix) Student.cpp

$(IntermediateDirectory)/MedicalRecord.cpp$(ObjectSuffix): MedicalRecord.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/MK/Documents/courseproject/stable/MedicalRecord.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MedicalRecord.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MedicalRecord.cpp$(PreprocessSuffix): MedicalRecord.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MedicalRecord.cpp$(PreprocessSuffix) MedicalRecord.cpp

$(IntermediateDirectory)/Time.cpp$(ObjectSuffix): Time.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/MK/Documents/courseproject/stable/Time.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Time.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Time.cpp$(PreprocessSuffix): Time.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Time.cpp$(PreprocessSuffix) Time.cpp

$(IntermediateDirectory)/MedicalRecordList.cpp$(ObjectSuffix): MedicalRecordList.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/MK/Documents/courseproject/stable/MedicalRecordList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MedicalRecordList.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MedicalRecordList.cpp$(PreprocessSuffix): MedicalRecordList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MedicalRecordList.cpp$(PreprocessSuffix) MedicalRecordList.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/MK/Documents/courseproject/stable/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


