@echo off
set VLC=vlc.exe
set /p yturl=Youtube URL (right-click): 
youtube-dl.exe -F %yturl:&=^&%

set /p ytdlfmt=Video Format: 
youtube-dl.exe -g -f %ytdlfmt% %yturl:&=^&% > %TEMP%\yt-dl.m3u

set /p audioytdlfmt=Audio Format: 
youtube-dl.exe -g -f %audioytdlfmt% %yturl:&=^&% > %TEMP%\ayt-dl.m3u
set /p audio= < %TEMP%\ayt-dl.m3u

youtube-dl --list-subs %yturl:&=^&%
set /p subytdlfmt=Subtitle Language: 
youtube-dl --write-sub --sub-lang %subytdlfmt% --skip-download %yturl:&=^&% -o %TEMP%\sub

%VLC% --meta-title="%yturl%" %TEMP%\yt-dl.m3u --input-slave="%audio%" --sub-file=%TEMP%\sub.%subytdlfmt%.vtt
