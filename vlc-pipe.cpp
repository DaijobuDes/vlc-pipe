#include <cstdio>
#include <cstdlib>
#include <cstring>

#define CLEAR system("cls")

char* load_file(char const* path);

int main()
{
    int run = 1;
    while(run)
    {
        CLEAR;
        char url[] = "\0", videoFormat[16], audioFormat[16], subFormat[8] = "ttml", lang[8] = "en";

        system("mkdir C:\\vlc-pipe >nul 2>nul");
        system("del /F /Q C:\\vlc-pipe\\* >nul 2>nul");

        printf("Youtube URL (right-click): ");
        scanf("%s", &url);

        char cmdVideoFormatList[256] = "youtube-dl -F ";
        strcat(cmdVideoFormatList, url);
        system(cmdVideoFormatList);

        printf("Video Format: ");
        scanf("%s", &videoFormat);
        char cmdVideoFormat[256] = "youtube-dl -g -f ";
        strcat(cmdVideoFormat, videoFormat);
        strcat(cmdVideoFormat, " ");
        strcat(cmdVideoFormat, url);
        strcat(cmdVideoFormat, " > C:\\vlc-pipe\\vyt-dl.m3u");
        system(cmdVideoFormat);

        printf("Audio Format: ");
        scanf("%s", &audioFormat);
        char cmdAudioFormat[256] = "youtube-dl -g -f ";
        strcat(cmdAudioFormat, audioFormat);
        strcat(cmdAudioFormat, " ");
        strcat(cmdAudioFormat, url);
        strcat(cmdAudioFormat, " > C:\\vlc-pipe\\ayt-dl.m3u");
        system(cmdAudioFormat);

        CLEAR;

        fflush(stdin);
        fflush(stdout);

        char listSubtitles[256] = "youtube-dl --list-subs ";
        strcat(listSubtitles, url);
        system(listSubtitles);

        printf("Subtitle language and format (lang, format): ");
        scanf("%s %s", &lang, &subFormat);
        system("del C:\\vlc-pipe\\sub* >nul 2>nul");
        char cmdSubtitleFormat[256] = "youtube-dl --write-sub --sub-lang ";
        strcat(cmdSubtitleFormat, lang);
        strcat(cmdSubtitleFormat, " --skip-download --sub-format ");
        strcat(cmdSubtitleFormat, subFormat);
        strcat(cmdSubtitleFormat, " \"");
        strcat(cmdSubtitleFormat, url);
        strcat(cmdSubtitleFormat, "\" -o C:\\vlc-pipe\\sub");
        system(cmdSubtitleFormat);

        CLEAR;

        char runCommand[2048] = "vlc.exe --meta-title=";
        strcat(runCommand, url);
        strcat(runCommand, " C:\\vlc-pipe\\vyt-dl.m3u --sub-file=C:\\vlc-pipe\\sub.");
        strcat(runCommand, lang);
        strcat(runCommand, ".");
        strcat(runCommand, subFormat);
        strcat(runCommand, " --input-slave=\"");
        strcat(runCommand, load_file("C:\\vlc-pipe\\ayt-dl.m3u"));
        strcat(runCommand, "\"");

        printf("Currently playing %s", url);
        system(runCommand);

        printf("\n\nEnter URL again? (1/0): ");
        scanf("%d", &run);
    }

    return 0;
}

char *load_file(char const* path)
{
    char* buffer = 0;
    long length;
    FILE * f = fopen(path, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell (f);
        fseek(f, 0, SEEK_SET);
        buffer = (char*)malloc ((length+1)*sizeof(char));
        if(buffer)
        {
            fread (buffer, sizeof(char), length, f);
        }
        fclose(f);
    }
    buffer[length] = '\0';
    // for (int i = 0; i < length; i++) {
    //     printf("buffer[%d] == %c\n", i, buffer[i]);
    // }
    //printf("buffer = %s\n", buffer);

    return buffer;
}