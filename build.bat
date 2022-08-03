@echo off

:: NOTE(tiny) - ensure \bin\setup_cl_generic.bat is set up correctly.
:: Use Visual Studio 2022's vsvarsall.bat if you can't compile. (I use Visual Studio 2022 Build Tools)

call ..\bin\buildsuper_x64-win.bat 4coder_modal.cpp

if exist 4coder_modal.cpp (
	if exist custom_4coder.dll (
		move /Y custom_4coder.dll ..\..\
	)

	if exist custom_4coder.pdb (
		move /Y custom_4coder.pdb ..\..\
	)
) else (
	if exist custom_4coder.dll (
		move /Y custom_4coder.dll ..\
	)

	if exist custom_4coder.pdb (
		move /Y custom_4coder.pdb ..\
	)
)

if exist vc140.pdb (
	del vc140.pdb
)