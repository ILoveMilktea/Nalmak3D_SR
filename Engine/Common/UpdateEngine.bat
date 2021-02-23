xcopy /y ..\Include\*.h ..\..\Ref\Include\
xcopy /y ..\Bin\*.dll ..\..\Client\Bin\Win32\Debug\
xcopy /y ..\Bin\*.dll ..\..\Client\Bin\Win32\Release\
xcopy /y ..\Bin\*.dll ..\..\Client\Bin\x64\Debug\
xcopy /y ..\Bin\*.dll ..\..\Client\Bin\x64\Release\
xcopy /y ..\Bin\*.lib ..\..\Ref\Lib\

xcopy /y ..\Bin\*.dll ..\..\EffectTool\
xcopy /y ..\Bin\*.lib ..\..\EffectTool\
xcopy /y ..\Include\*.h ..\..\EffectTool\Include\

xcopy /y ..\Bin\*.dll ..\..\TerrainTool\
xcopy /y ..\Bin\*.lib ..\..\TerrainTool\
xcopy /y ..\Include\*.h ..\..\TerrainTool\Include\