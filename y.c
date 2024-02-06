#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <windows.h>
#include <errno.h>
#include <libgen.h>
#include <time.h>
#include <fcntl.h>
#include <tchar.h>
#define MAX_SENTENCES 100
/*int static_error_check(char *file_path) {
    FILE *formats = fopen(file_path, "r");
    int flag = 0;
    char *format = malloc(1000);
    while (fgets(format, 1000, formats) != NULL) {
        if (format[strlen(format) - 1] == '\n') {
            format[strlen(format) - 1] = '\0';
        }

        if (strcmp(format, ".c") == 0 || strcmp(format, ".cpp") == 0) {
            if (strstr(file_path, format) != NULL) {
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0) {
        return 2;
    }
    char *input = malloc(1000);
    strcpy(input, "gcc ");
    strcat(input, file_path);
    strcat(input, " -o mamad > /dev/null 2>&1");
    int status = system(input);
    if (status != 0) {
        return 0;
    }
    return 1;
}*/

int fileExists(const char *filePath) //
{
    return access(filePath, F_OK) == 0;
}

void removeSpaces(char *str)
{
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ')
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int hasDot(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '.')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

void copyFolder(char source[], char destination[])
{
    char input[100];
    sprintf(input, "xcopy /E /I /Y \"%s\" \"%s\"", source, destination);
    system(input);
}

int compareTimes(char *time1, char *time2)
{
    int hour1, min1, sec1;
    int hour2, min2, sec2;
    sscanf(time1, "%d:%d:%d", &hour1, &min1, &sec1);
    sscanf(time2, "%d:%d:%d", &hour2, &min2, &sec2);
    int total1 = hour1 * 3600 + min1 * 60 + sec1;
    int total2 = hour2 * 3600 + min2 * 60 + sec2;
    if (total1 > total2)
    {
        return 1;
    }
    if (total1 < total2)
    {
        return 0;
    }
}

int compareTimes2(char *time1, char *time2)
{
    int hour1, min1, sec1;
    int hour2, min2, sec2;
    sscanf(time1, "%d:%d:%d", &hour1, &min1, &sec1);
    sscanf(time2, "%d:%d:%d", &hour2, &min2, &sec2);
    int total1 = hour1 * 3600 + min1 * 60 + sec1;
    int total2 = hour2 * 3600 + min2 * 60 + sec2;
    if (total1 > total2)
    {
        return 0;
    }
    if (total1 < total2)
    {
        return 1;
    }
}

void printSentencesInReverseOrder(FILE *file)
{
    char sentences[MAX_SENTENCES][100];
    int count = 0;

    // Read sentences from file and store them in an array
    while (fgets(sentences[count], 100, file) != NULL)
    {
        count++;
    }

    // Print sentences in reverse order
    for (int i = count - 1; i >= 0; i--)
    {
        printf("%s", sentences[i]);
    }
}

void ReverseFile(FILE *file)
{
    char currentDirectory[FILENAME_MAX];
    _fullpath(currentDirectory, ".", FILENAME_MAX);
    strcat(currentDirectory, "\\bizhbi"); // way of bizhbi (where i make files to manage my bizhbi)
    addBackslashes(currentDirectory);
    char temp_loog[100];
    strcpy(temp_loog, currentDirectory);
    strcat(temp_loog, "\\\\temp_log.txt");
    char sentences[MAX_SENTENCES][100];
    int count = 0;
    FILE *temp = fopen(temp_loog, "w");
    while (fgets(sentences[count], 100, file) != NULL)
    {
        count++;
    }
    for (int i = count - 1; i >= 0; i--)
    {
        fprintf(temp, "%s", sentences[i]);
    }
    fclose(temp);
}

void reverseForLog(FILE *file, int number)
{
    char sentences[MAX_SENTENCES][100];

    int count = 0;
    int save = 0;
    // Read sentences from file and store them in an array
    while (fgets(sentences[count], 100, file) != NULL)
    {
        count++;
    }

    // Print sentences in reverse order
    for (int i = count - 1; i >= 0; i--)
    {

        if (save == (number * 7))
        {
            break;
        }
        else
        {
            printf("%s", sentences[i]);
            save++;
        }
    }
}

void replaceDotWithNull(char *str)
{
    while (*str != '\0')
    {
        if (*str == '.')
        {
            *str = '\0';
            return; // Stop after the first occurrence is replaced
        }
        str++;
    }
}

bool directoryExists(char *path)
{
    struct stat info;
    if (stat(path, &info) != 0)
    {
        return false;
    }
    return S_ISDIR(info.st_mode);
}

int matchhh(char *pattern, char *text)
{
    // for null characters.
    if (*pattern == '\0' && *text == '\0')
    {
        return 1;
    }
    // for *a;
    if (*pattern == '*' && *(pattern + 1) != '\0' && *text == '\0')
    {
        return 0;
    }
    if (*pattern == *text)
    {
        return matchhh(pattern + 1, text + 1);
    }
    if (*pattern == '*')
    {
        return matchhh(pattern + 1, text) || matchhh(pattern, text + 1);
    }
    return 0;
}

void saparetor(char user[200], char saved[200])
{
    int start = 0;
    int end = 0;
    int len1 = strlen(user);
    for (int i = 0; i < len1; i++)
    {
        if (user[i] == '\"')
        {
            start = i;
            break;
        }
    }
    end = len1 - 1;
    int i = 0;
    for (int j = start + 1; j < end; j++)
    {
        saved[i] = user[j];
        i++;
    }
    saved[i] = '\0';
}

int token_del(char *name_of_files[1000], char user[100])
{
    int count = -1;
    int input = 0;
    char del[100] = "<>";
    char *ptr = strtok(user, del);
    while (ptr != NULL)
    {
        count++;
        if (count != 0)
        {
            name_of_files[input] = ptr;
            input++;
        }
        ptr = strtok(NULL, del);
    }
    return input;
}

void addBackslashes(char *str)
{
    int length = strlen(str);

    for (int i = 0; i < length; i++)
    {
        if (str[i] == '\\')
        {
            memmove(&str[i + 2], &str[i + 1], (length - i));
            str[i + 1] = '\\';
            length++;
            i++; // Skip the next character to avoid an infinite loop
        }
    }
}

void reset_for_directory(const char *filename, char *name)
{
    char currentDirectory[FILENAME_MAX];
    char for_temp_for_dir[FILENAME_MAX];
    char for_unstage_file[FILENAME_MAX];
    char for_staging_file[FILENAME_MAX];
    char for_t_txt[FILENAME_MAX];
    _fullpath(currentDirectory, ".", FILENAME_MAX);
    strcat(currentDirectory, "\\bizhbi");
    strcpy(for_unstage_file, currentDirectory);
    strcat(for_unstage_file, "\\\\unstage.txt");
    strcpy(for_temp_for_dir, currentDirectory);
    strcat(for_temp_for_dir, "\\\\temp_for_dir.txt");
    strcpy(for_staging_file, currentDirectory);
    strcat(for_staging_file, "\\\\staging.txt");
    strcpy(for_t_txt, currentDirectory);
    strcat(for_t_txt, "\\\\t.txt");

    struct stat path_stat_d;
    DIR *dir;
    char line_d[1000];
    struct dirent *entry;
    dir = opendir(name);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: cannot open the staging file.\n");
        // return 1;
    }
    FILE *temp_file = fopen(for_temp_for_dir, "a");
    if (temp_file == NULL)
    {
        printf("Error: cannot create a temporary file.\n");
        fclose(file);
        // return 1;
    }
    FILE *unstaged = fopen(for_unstage_file, "a");
    if (unstaged == NULL)
    {
        printf("Error: cannot create unstaged file.\n");
        fclose(file);
        fclose(temp_file);
        // return 1;
    }
    fclose(file);
    fclose(temp_file);
    fclose(unstaged);
    file = fopen(filename, "r");
    temp_file = fopen(for_temp_for_dir, "a");
    unstaged = fopen(for_unstage_file, "a");
    // int matchhh = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0))
        {
            fprintf(temp_file, "%s\n", entry->d_name);
        }
    }
    fprintf(temp_file, "%s\n", basename(name));
    char line1[1000];
    char line2[1000];
    fclose(temp_file);
    fclose(file);
    fclose(unstaged);
    closedir(dir);
    FILE *file1, *file2, *file3;
    file1 = fopen(for_temp_for_dir, "r");
    file2 = fopen(for_staging_file, "r");
    unstaged = fopen(for_unstage_file, "a");
    while (fgets(line1, sizeof(line1), file1) != NULL)
    {
        line1[strcspn(line1, "\n")] = '\0';

        rewind(file2);
        while (fgets(line2, sizeof(line2), file2) != NULL)
        {
            line2[strcspn(line2, "\n")] = '\0';
            if (strcmp(line1, line2) == 0)
            {
                fprintf(unstaged, "%s\n", line2);
            }
        }
    }

    fclose(file1);
    fclose(file2);
    fclose(unstaged);
    remove(for_temp_for_dir);
    fclose(file2);
    fclose(temp_file);
    FILE *fp1 = fopen(for_staging_file, "r");
    FILE *fp2 = fopen(for_unstage_file, "r");
    FILE *temp = fopen(for_t_txt, "a");

    char line11[100];
    char line12[100];
    int matchhh;

    while (fgets(line11, sizeof(line11), fp1))
    {
        line11[strcspn(line11, "\n")] = '\0';
        matchhh = 0;
        rewind(fp2);

        while (fgets(line12, sizeof(line12), fp2))
        {
            line12[strcspn(line12, "\n")] = '\0';
            if (strcmp(line11, line12) == 0)
            {
                matchhh = 1;
                break;
            }
        }

        if (!matchhh)
        {
            fputs(line11, temp);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(temp);
    remove(for_staging_file);
    rename(for_t_txt, for_staging_file);
    fclose(temp);
    fclose(fp2);
}

void extractText(char *str, char userName[])
{
    int start = -1;
    int end = -1;
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        if (str[i] == '\"')
        {
            if (start == -1)
            {
                start = i + 1;
            }
            else
            {
                end = i;
                break;
            }
        }
    }
    userName[end - start + 1];
    strncpy(userName, str + start, end - start);
    userName[end - start] = '\0';
}

void saparetorWordInFile(char *filename, char *word, int saved[100])
{
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int line = 1;
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        char *token = strtok(buffer, " \t\n");
        while (token != NULL)
        {
            if (strcmp(token, word) == 0)
            {
                saved[i] = line;
                printf("%d", saved[i]);
                i++;
            }
            token = strtok(NULL, " \t\n");
        }
        line++;
    }
    fclose(file);
}

int saparetorWordInFile1(char *filename, char *word)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return -1;
    }
    int flag = 0;
    char buffer[256];
    int line = 1;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        char *token = strtok(buffer, " \t\n");

        while (token != NULL)
        {
            if (strcmp(token, word) == 0)
            {
                flag = 1;
                break;
            }
            token = strtok(NULL, " \t\n");
        }
        if (flag == 1)
        {
            break;
        }
        line++;
    }
    fclose(file);
    return line;
}

void deleteTextFiles(char *directory) // for deleting text fiels of user and updating them.
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(directory);
    if (dir == NULL)
    {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, ".") != NULL) // noooooooot sure
        {
            char *filename = entry->d_name;
            if (strstr(filename, ".txt") != NULL)
            {
                char filepath[256];
                snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);
                remove(filepath);
            }
        }
    }

    closedir(dir);
}

void tokenizeStrings(char *input, char **output, int *count) // for time that we have more that one " "
{
    int i = 0;
    int j = 0;
    int start = 0;
    int end = 0;
    int length = strlen(input);
    int inQuotes = 0;

    while (i < length)
    {
        if (input[i] == '"')
        {
            if (inQuotes)
            {
                end = i;
                int tokenLength = end - start - 1;
                output[j] = (char *)malloc((tokenLength + 1) * sizeof(char));
                strncpy(output[j], input + start + 1, tokenLength);
                output[j][tokenLength] = '\0';
                j++;
                inQuotes = 0;
            }
            else
            {
                start = i;
                inQuotes = 1;
            }
        }
        i++;
    }

    *count = j;
}

void isFormatCorrect(char *filename) // for pre commit - founding thye formats like pdf
{
    int len = strlen(filename);
    char *format = &filename[len - 3];
    if (strcmp(format, "txt") == 0)
    {
        printf("\033[0;31m");
        printf("format-check................................................PASSED\n");
    }
    else if (strcmp(format, "csv") == 0)
    {
        printf("\033[0;31m");
        printf("format-check................................................PASSED\n");
    }
    else if (strcmp(format, "jpg") == 0)
    {
        printf("\033[0;31m");
        printf("format-check................................................PASSED\n");
    }
    else if (strcmp(format, "png") == 0)
    {
        printf("\033[0;31m");
        printf("format-check................................................PASSED\n");
    }
    else if (strcmp(format, "pdf") == 0)
    {
        printf("\033[0;31m");
        printf("format-check................................................PASSED\n");
    }
    else if (strcmp(format, "doc") == 0)
    {
        printf("\033[0;31m");
        printf("format-check................................................PASSED\n");
    }
    else if (strcmp(format, "xls") == 0)
    {
        printf("\033[0;31m");
        printf("format-check................................................PASSED\n");
    }
    else
    {
        printf("\033[0;31m");
        printf("format-check................................................FAILED\n");
    }
}

void checkFileTimes(char *filename) // for pre-commit finding the times.
{
    struct stat fileStat;
    char *base = basename(filename);
    char extension[4];
    int len = strlen(base);
    strncpy(extension, base + len - 3, 3);
    extension[3] = '\0';
    if (stat(filename, &fileStat) == 0)
    {
        time_t currentTime = time(NULL);
        time_t fileModifiedTime = fileStat.st_mtime;
        time_t timeDifference = currentTime - fileModifiedTime;

        if (timeDifference > 600 && (strcmp(extension, "mp4") == 0 || strcmp(extension, "wav") == 0 || strcmp(extension, "mp3") == 0))
        {
            printf("\033[0;32m"); // Set color to green
            printf("time-limit................................................PASSED\n");
        }
        else if (strcmp(extension, "mp4") == 0 || strcmp(extension, "wav") == 0 || strcmp(extension, "mp3") == 0)
        {
            printf("\033[0;32m"); // Set color to green
            printf("time-limit................................................FAILED\n");
        }
        else
        {
            printf("\033[0;32m"); // Set color to green
            printf("time-limit................................................SKIPPED\n");
        }
    }
    else
    {
        printf("Error occurred while checking file times.\n");
    }
}

void isFileLarge(char *filename) // for pre-commit finding the size of file.
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fclose(file);

    if (fileSize > 5 * 1024 * 1024)
    {
        printf("\033[0;34m"); // Set color to blue
        printf("file-size-check................................................FAILED\n");
    }
    else
    {
        printf("\033[0;34m"); // Set color to blue
        printf("file-size-check................................................PASSED\n");
    }
}

void characters(char *filename) // for pre-commit finding the characters more than 200000
{
    char *base = basename(filename);
    char extension[4];
    int len = strlen(base);
    strncpy(extension, base + len - 3, 3);
    extension[3] = '\0';
    FILE *file = fopen(filename, "r");
    if (strcmp(extension, "c") == 0 || strcmp(extension, "cpp") == 0 || strcmp(extension, "txt") == 0)
    {
        char word[100];
        int count = 0;

        while (fscanf(file, "%s", word) != EOF)
        {
            count++;
        }

        if (count > 20000)
        {
            printf("character-check................................................FAILED\n");
        }
        else
        {
            printf("character-check................................................PASSED\n");
        }
    }
    else
    {
        printf("character-check................................................SKIPPED\n");
    }
    fclose(file);
}

void whitespace(char *filename) // for pre-commit finding whitspces
{
    char *base = basename(filename);
    char extension[5];
    strncpy(extension, base + strlen(base) - 3, 3);
    extension[3] = '\0';

    if (strcmp(extension, "txt") == 0 || strcmp(extension, "cpp") == 0 || strcmp(extension, "c") == 0)
    {
        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("File not found.\n");
            // return 1;
        }

        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, -1, SEEK_END);
        int lastChar = fgetc(file);

        if (lastChar == ' ' || lastChar == '\n')
        { // fail
            printf("\033[0;32m");
            printf("eof_blank_space................................................FAILED\n");
        }
        else
        {
            printf("\033[0;32m");
            printf("eof_blank_space................................................PASSED\n");
        }

        fclose(file);
    }
    else
    {
        printf("\033[0;32m");
        printf("eof_blank_space................................................SKIPPED\n");
    }
}

void TODO(char *file_name)
{
    char *base = basename(file_name);
    FILE *file = fopen(file_name, "r");
    const char *extension = strrchr(base, '.');
    int flag_for_com = 1;
    if (strcmp(extension, ".c") == 0 || strcmp(extension, ".cpp") == 0)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            line[strcspn(line, "\n")] = '\0';
            if (strstr(line, "//TODO") || strcmp(line, "//TODO") == 0)
            {
                printf("todo_check................................................FAILED\n");
                flag_for_com = 0;
                break;
            }
        }
        if (flag_for_com == 1)
        {
            printf("todo_check................................................PASSED\n");
        }
    }
    if (strcmp(extension, ".txt") == 0)
    {
        char line1[256];
        while (fgets(line1, sizeof(line1), file))
        {
            line1[strcspn(line1, "\n")] = '\0';
            if (strstr(line1, "TODO") || strcmp(line1, "TODO") == 0)
            {
                printf("todo_check................................................FAILED\n");
                flag_for_com = 0;
                break;
            }
        }
        if (flag_for_com == 1)
        {
            printf("todo_check................................................PASSED\n");
        }
    }
    else
    {
        printf("todo_check................................................SKIPPED\n");
    }
    fclose(file);
}

int main()
{
    char currentDirectory[FILENAME_MAX];
    char copy_currentDirectory[FILENAME_MAX];
    char copy_cur_for_master[FILENAME_MAX];
    char main_copy_of_exe_path_of_code[FILENAME_MAX];
    char cop_for_status[FILENAME_MAX];
    _fullpath(currentDirectory, ".", FILENAME_MAX);
    strcpy(main_copy_of_exe_path_of_code, currentDirectory); // attention this is the way i have code's exe and area of user.

    strcat(currentDirectory, "\\bizhbi"); // way of bizhbi (where i make files to manage my bizhbi)
    addBackslashes(currentDirectory);
    strcpy(copy_cur_for_master, currentDirectory);
    strcpy(copy_currentDirectory, currentDirectory);
    char input[200];
    int exists_config_name = 0;
    int exists_config_email = 0;
    char saverrr[200];      // for username;
    char saving_email[200]; // for email;
    char file_address[256][256];
    strcat(copy_currentDirectory, "\\global_config.txt");
    // be careful about the directory path.
    char *directoryPath = copy_currentDirectory;
    struct stat directoryStat;
    char first_name_cond[100][100];
    char shortcut[256];
    char shortcut_message[256];
    int countt = 0;
    int i_s = 0;
    int commit_id = 1;
    char copy_one_cu[260];
    strcpy(copy_one_cu, main_copy_of_exe_path_of_code);
    strcpy(cop_for_status, currentDirectory);
    addBackslashes(cop_for_status);
    FILE *global_config_file;
    char copy_branch[100];
    strcpy(copy_branch, currentDirectory);
    strcat(copy_branch, "\\\\branch.txt");
    FILE *branch = fopen(copy_branch, "a");
    fseek(branch, 0, SEEK_END);
    long size = ftell(branch);
    if (size == 0)
    {
        fputs("master\n", branch);
    }
    fclose(branch);
    FILE *config_file;
    char copy_staging[100];
    strcpy(copy_staging, currentDirectory);
    strcat(copy_staging, "\\\\staging.txt");
    // printf("%s", copy_staging);
    FILE *staging = fopen(copy_staging, "a");
    fclose(staging);
    char copy_head[100];
    strcpy(copy_head, currentDirectory);
    strcat(copy_head, "\\\\head.txt");
    FILE *head = fopen(copy_head, "a");
    fclose(head);
    char copy_unstage[100];
    strcpy(copy_unstage, currentDirectory);
    strcat(copy_unstage, "\\unstage");
    char cop_depth[100];
    strcpy(cop_depth, currentDirectory);
    strcat(cop_depth, "\\\\depth.txt");
    char cop_unstage[100];
    strcpy(cop_unstage, currentDirectory);
    strcat(cop_unstage, "\\\\unstage.txt");
    char temppp[100];
    strcpy(temppp, currentDirectory);
    strcat(temppp, "\\\\temp_for_file.txt");
    char temp_b[100];
    strcpy(temp_b, currentDirectory);
    strcat(temp_b, "\\\\temp_b.txt");
    char file_temp[100];
    strcpy(file_temp, currentDirectory);
    strcat(file_temp, "\\\\temp_for_file.txt");
    char shortt[100];
    strcpy(shortt, currentDirectory);
    strcat(shortt, "\\\\shortcut.txt");
    char copy_commit[100];
    strcpy(copy_commit, currentDirectory);
    strcat(copy_commit, "\\\\commit.txt");
    char temp_shortt[100];
    strcpy(temp_shortt, currentDirectory);
    strcat(temp_shortt, "\\\\temp_commit.txt");
    char temp_loog[100];
    strcpy(temp_loog, currentDirectory);
    strcat(temp_loog, "\\\\temp_log.txt");
    FILE *commit = fopen(copy_commit, "a");
    fclose(commit);
    DIR *dir_1;
    struct dirent *entry_1;
    // Open the directory
    dir_1 = opendir(copy_one_cu); // user area - status
    // Read each entry in the directory
    while ((entry_1 = readdir(dir_1)) != NULL)
    {
        if (strcmp(entry_1->d_name, ".") != 0 && strcmp(entry_1->d_name, "..") != 0)
        {
            strcpy(first_name_cond[countt], entry_1->d_name);
            countt++;
        }
    }
    closedir(dir_1);

    struct stat filestat;
    time_t lastModifiedTime[256];

    for (int i = 0; i < countt; i++) // for status and copying.
    {
        snprintf(file_address[i], sizeof(file_address[i]), "%s\\%s", copy_one_cu, first_name_cond[i]); // making address.
        stat(file_address[i], &filestat);
        lastModifiedTime[i] = filestat.st_mtime;
    }
    char temp_f[100];
    strcpy(temp_f, currentDirectory);
    strcat(temp_f, "\\\\temp_f.txt");
    char copy10[100];
    strcpy(copy10, currentDirectory);
    strcat(copy10, "\\branch");
    mkdir(copy10);
    char messsage[100];
    strcpy(messsage, currentDirectory);
    strcat(messsage, "\\\\message.txt");
    char copy_master[100];
    strcpy(copy_master, currentDirectory);
    strcat(copy_master, "\\branch\\master");
    char copy_config[100];
    strcpy(copy_config, currentDirectory);
    strcat(copy_config, "\\\\config.txt");
    char temp_c[100];
    strcpy(temp_c, currentDirectory);
    strcat(temp_c, "\\\\temp_c.txt");
    char global[100];
    strcpy(global, currentDirectory);
    strcat(global, "\\\\global_config.txt");
    char copy_info_saver[100];
    strcpy(copy_info_saver, currentDirectory);
    strcat(copy_info_saver, "\\\\user_saver.txt");
    char remoov[100];
    strcpy(remoov, currentDirectory);
    strcat(remoov, "\\\\delet.txt");
    char copy_fstaging[100];
    strcpy(copy_fstaging, currentDirectory);
    strcat(copy_fstaging, "\\staging");
    char copy_commi[100];
    strcpy(copy_commi, currentDirectory);
    strcat(copy_commi, "\\commit");
    if (access(currentDirectory, F_OK) != -1)
    {
        if (access(copy_master, F_OK) == -1)
        {
            mkdir(copy_master);
            char dastor22[100];
            sprintf(dastor22, "move %s %s", copy_master, copy10);
            system(dastor22);
        }
    }

    while (1)
    {
        gets(input);

        if (strncmp(input, "bizhbi init", 11) == 0)
        {
            DIR *dir = opendir("."); // . is working directory.
            int flag = 0;
            char tmp_cwd[2000];
            char cwd[2000];
            bool exists = false;
            char input[1000];
            char hey[] = "bizhbi";
            sprintf(input, "dir \"/%s\" /s", hey);
            /*if(system(input)){
             printf("bizhbi has been already exists in other folders.");
             continue;
         }*/
            if (dir)
            {
                struct dirent *entry;
                while ((entry = readdir(dir)) != NULL)
                {
                    if (strcmp(entry->d_name, "bizhbi") == 0)
                    {
                        printf("The directory 'bizhbi' exists in the root folder.\n");
                        flag = 1;
                        exists = true;
                        break;
                    }
                }
                if (flag == 0)
                {

                    system("mkdir bizhbi");
                    printf("the intilization has been done succesfully");
                    continue;
                }
                closedir(dir);
                if (getcwd(cwd, sizeof(cwd)) == NULL)
                    continue;
                if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL)
                    continue;
            }
            // checking that the directory has been made or not.
            if (strcmp(tmp_cwd, "/") != 0)
            {
                if (chdir("..") != 0)
                    continue;
            }
            while (strcmp(tmp_cwd, "/") != 0)
            {
                if (chdir(cwd) != 0)
                {
                    continue;
                }
            }
        }

        else if (strncmp(input, "bizhbi config global -username", 30) == 0)
        {

            if (access(directoryPath, F_OK) != -1)
            {
                printf("you'v already set your email and name.");
            }
            else
            {
                saparetor(input, saverrr);
            }
        }

        else if (strncmp(input, "bizhbi config global -email", 27) == 0)
        {

            if (access(directoryPath, F_OK) != -1)
            {
                printf("you'v already set your email and name.");
            }
            else
            {
                saparetor(input, saving_email);
                config_file = fopen(directoryPath, "w");
                //
                fprintf(config_file, "Username : %s \n", saverrr);
                fprintf(config_file, "Useremail : %s \n", saving_email);
                // extra info for other inputs.
                fprintf(config_file, "last_commit_id : %d\n", 0);
                fprintf(config_file, "current_commit_id : %d\n", 0);
                fprintf(config_file, "branch : %s\n", "master");
                fclose(config_file);
                printf("you set your global name and global email succsefully.");
                exists_config_name = 1;
            }
            exists_config_email = 1;
        }

        else if (strncmp(input, "bizhbi config -username", 23) == 0)
        {
            if (access(directoryPath, F_OK) != -1)
            {
                printf("you'v already set your email.");
            }
            else
            {
                saparetor(input, saverrr);
            }
        }

        else if (strncmp(input, "bizhbi config -email", 20) == 0)
        {

            if (access(directoryPath, F_OK) != -1)
            {
                printf("you'v already set your email.");
            }
            else
            {
                saparetor(input, saving_email);
                config_file = fopen(copy_config, "a");
                fprintf(config_file, "Username : %s \n", saverrr);
                fprintf(config_file, "Useremail : %s \n", saving_email);
                // extra info for other inputs.
                fprintf(config_file, "last_commit_id : %d\n", 0);
                fprintf(config_file, "current_commit_id : %d\n", 0);
                fprintf(config_file, "branch : %s\n", "master");
                fclose(config_file);
                printf("you set your name and email succsefully.");

                FILE *info_saver = fopen(copy_info_saver, "w");
                fprintf(info_saver, "Username : %s\n", saverrr);
                fprintf(info_saver, "Useremail : %s\n", saving_email);
                fclose(info_saver);
            }
        }

        else if (strncmp(input, "bizhbi add", 10) == 0 && strstr(input, "*") == NULL && strncmp(input, "bizhbi add -f", 13) != 0 && strncmp(input, "bizhbi add depth", 16) != 0 && strncmp(input, "bizhbi add -redo", 16) != 0)
        {

            mkdir(copy_fstaging);
            char path[100];
            int found_1 = 0;
            int found_2 = 0;
            saparetor(input, path);
            if (access(path, F_OK) == 0)
            {
                if (directoryExists(path))
                {
                    DIR *dir;
                    struct dirent *entry;

                    // Open the directory
                    dir = opendir(path);
                    if (dir == NULL)
                    {
                        printf("something wrong happend. please try again.");
                        continue;
                    }
                    while ((entry = (readdir(dir))) != NULL)
                    {
                        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                        {
                            char *dir_name = basename(entry->d_name);
                            staging = fopen(copy_staging, "r");
                            if (staging == NULL)
                                printf("something wrong happend. plaese try again...\n"); // for sure.
                            int len = strlen(dir_name);
                            dir_name[len] = '\0';
                            char line[100];
                            while (fgets(line, (sizeof(line)), staging))
                            {
                                if (strstr(line, dir_name) != NULL)
                                {
                                    found_2 = 1;
                                    break;
                                }
                            }
                            if (found_2 == 0)
                            {

                                staging = fopen(copy_staging, "a");
                                fprintf(staging, "%s\n", dir_name);
                                fclose(staging);
                            }
                        }
                    }
                    if (found_2 == 1)
                    {
                        printf("this directory has been already on stage mood.");
                        continue;
                    }
                    else
                    {
                        char copy1[100];
                        char copy_path[100];
                        strcpy(copy1, currentDirectory);
                        strcpy(copy_path, path);
                        strcat(copy1, "\\staging");
                        copyFolder(path, copy1);
                        printf("your directory is on stage mood now.");
                        char *path_temp = basename(path);
                        staging = fopen(copy_staging, "a");
                        fprintf(staging, "%s\n", path_temp);
                        fclose(staging);
                    }
                }

                else
                {
                    // first we check that we have this address in our file or not.
                    staging = fopen(copy_staging, "r");
                    if (staging == NULL)
                        printf("something wrong happend. plaese try again.");
                    int len = strlen(path);
                    path[len] = '\0';
                    char line[100];
                    char *temp_path = basename(path);
                    while (fgets(line, sizeof(line), staging))
                    {
                        if (strstr(line, temp_path) != NULL)
                        {
                            found_1 = 1;
                            break;
                        }
                    }
                    fclose(staging);
                    if (found_1 == 1)
                    {
                        printf("this file has been already on stage mood.");
                    }
                    else
                    {
                        staging = fopen(copy_staging, "a");
                        if (staging == NULL)
                            printf("something wrong happend. olease try again.");
                        char copy11[100];
                        char copy_path[100];
                        strcpy(copy11, currentDirectory);
                        strcpy(copy_path, path);
                        strcat(copy11, "\\staging");
                        char dastor[100];
                        char com[100];
                        sprintf(dastor, "copy %s %s", path, copy11);
                        system(dastor);
                        char copp[100];
                        strcpy(copp, currentDirectory);
                        strcat(copp, "\\branch\\master");
                        sprintf(com, "copy %s %s", path, copp);
                        system(com);
                        fprintf(staging, "%s\n", temp_path);
                        fclose(staging);
                        printf("your file is on stage mood now.");
                    }
                }
            }
            else
            {
                printf("we dont have such a file or directory");
            }
        }

        else if (strstr(input, "*") != NULL)
        {
            mkdir(copy_fstaging);
            char file_star[1000];
            saparetor(input, file_star);
            int counter = 0;
            char names_of_files[100][100];
            char names_of_dir[100][100];
            DIR *dir;
            struct dirent *entry;
            dir = opendir(main_copy_of_exe_path_of_code);
            // Check if the directory was opened successfully
            if (dir == NULL)
            {
                printf("1 - Unable to open the directory.\n");
            }
            // Read each entry in the directory
            while ((entry = readdir(dir)) != NULL)
            {
                // Ignore the "." and ".." entries
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                {
                    strcpy(names_of_files[counter], entry->d_name);
                    // printf("%s\n",names_of_files[counter]);
                    counter++;
                }
            }
            closedir(dir);

            for (int i = 0; i < counter; i++)
            {
                if (strstr(names_of_files[i], ".") == NULL)
                {
                    if (matchhh(file_star, names_of_files[i]))
                    {
                        char string[150];
                        strcpy(string, main_copy_of_exe_path_of_code);
                        strcat(string, "\\");
                        strcat(string, names_of_files[i]);
                        char copy1[100];
                        strcpy(copy1, currentDirectory);
                        strcat(copy1, "\\staging");
                        char dastor[100];
                        sprintf(dastor, "copy %s %s", string, copy1);
                        system(dastor);
                        // printf("%s\n", string);
                        DIR *dir;
                        int counter_dir = 0;
                        struct dirent *entry;
                        dir = opendir(string);
                        // Check if the directory was opened successfully
                        if (dir == NULL)
                        {
                            printf("2 - Unable to open the directory.\n");
                        }
                        // Read each entry in the directory
                        while ((entry = readdir(dir)) != NULL)
                        {
                            // Ignore the "." and ".." entries
                            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                            {
                                strcpy(names_of_dir[counter_dir], entry->d_name);
                                counter_dir++;
                            }
                        }
                        closedir(dir);
                        for (int j = 0; j < counter_dir; j++)
                        {
                            staging = fopen(copy_staging, "a");
                            if (staging == NULL)
                                printf("something wrong happend. please try again.");
                            char *temp = basename(names_of_dir[j]);
                            fprintf(staging, "%s\n", temp);
                            fclose(staging);
                        }
                        staging = fopen(copy_staging, "a");
                        char *temp1 = basename(string);
                        fprintf(staging, "%s\n", temp1);
                        fclose(staging);
                        printf("This directory is now in stage mood!\n");
                    }
                }
                else if (strstr(names_of_files[i], ".") != NULL)
                {
                    char m[100];
                    strcpy(m, names_of_files[i]);
                    char copy_name[100];
                    strcpy(copy_name, names_of_files[i]);
                    replaceDotWithNull(names_of_files[i]);
                    if (matchhh(file_star, names_of_files[i]))
                    {
                        char string[100];
                        strcpy(string, main_copy_of_exe_path_of_code);
                        strcat(string, "\\\\");
                        strcat(string, copy_name);
                        char copy1[100];
                        strcpy(copy1, currentDirectory);
                        strcat(copy1, "\\staging");
                        char dastor[100];
                        sprintf(dastor, "copy %s %s", string, copy1);
                        system(dastor);
                        int len = strlen(names_of_files[i]);
                        names_of_files[i][len] = '\0';
                        bool flag = false;
                        for (int i = 0; i <= counter; i++)
                        {
                            if (matchhh(file_star, names_of_files[i]))
                            {
                                staging = fopen(copy_staging, "a");
                                if (staging == NULL)
                                    printf("something wrong happend. please try again.");
                                fprintf(staging, "%s\n", m);
                                fclose(staging);
                                flag = true;
                            }
                        }
                        if (flag)
                        {
                            printf("your file is on stage mood..\n");
                        }
                        else
                        {
                            printf("we dont have such a file.");
                        }
                    }
                }
            }
        }

        else if (strncmp(input, "bizhbi add -f", 13) == 0)
        {
            mkdir(copy_fstaging);
            char *name[1000];
            int flag_for_f = 0;
            int y = token_del(name, input);
            for (int d = 0; d < y; d++)
            {
                if (strstr(name[d], ".") != NULL)
                {
                    flag_for_f = 0;
                    char *temp_name;
                    if (access(name[d], F_OK) == 0)
                    {
                        staging = fopen(copy_staging, "r");
                        /* if (staging == NULL)
                         {
                             printf("Something wrong happend. plase try again.");
                         }*/
                        int len = strlen(name[d]);
                        name[len - 1] = '\0';
                        temp_name = basename(name[d]);
                        char line[100];
                        while (fgets(line, sizeof(line), staging))
                        {
                            if (strstr(line, temp_name) != NULL)
                            {
                                flag_for_f = 1;
                                break;
                            }
                        }
                        fclose(staging);
                        if (flag_for_f == 1)
                        {
                            printf("%s has been already on stage mood.\n", temp_name);
                        }
                        else
                        {
                            char copy1[100];
                            strcpy(copy1, currentDirectory);
                            strcat(copy1, "\\staging");
                            char dastor[100];
                            sprintf(dastor, "copy %s %s", name[d], copy1);
                            system(dastor);
                            staging = fopen(copy_staging, "a");
                            // if (staging == NULL)
                            // printf("Something wrong happend. Please try again.");
                            fprintf(staging, "%s\n", temp_name);
                            fclose(staging);
                        }
                    }
                    else
                    {
                        printf("file %s is not exists", temp_name);
                    }
                }
                else if (strstr(name[d], ".") == NULL)
                {
                    int flag_for_2 = 0;
                    if (access(name[d], F_OK) == 0)
                    {
                        DIR *dir;
                        struct dirent *entry;

                        // Open the directory
                        dir = opendir(name[d]);
                        /* if (dir == NULL)
                         {
                             printf("something wrong happend. please try again.");
                             continue;
                         }*/
                        while ((entry = (readdir(dir))) != NULL)
                        {
                            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                            {
                                staging = fopen(copy_staging, "r");
                                // if (staging == NULL)
                                // printf("something wrong happend. plaese try again."); // for sure.
                                char *temp_name = basename(entry->d_name);
                                int len = strlen(temp_name);
                                temp_name[len - 1] = '\0';
                                char line[100];
                                while (fgets(line, (sizeof(line)), staging))
                                {
                                    if (strstr(line, temp_name) != NULL)
                                    {
                                        flag_for_2 = 1;
                                        break;
                                    }
                                }
                                if (flag_for_2 == 0)
                                {
                                    staging = fopen(copy_staging, "a");
                                    // if (staging == NULL)
                                    // printf("something wrong happend. please try again.");
                                    fprintf(staging, "%s\n", temp_name);
                                    fclose(staging);
                                }
                            }
                        }
                        if (flag_for_2 == 1)
                        {
                            printf("this directory has been already on stage mood.\n");
                        }
                        else if (flag_for_2 == 0)
                        {
                            char copy1[100];
                            strcpy(copy1, currentDirectory);
                            strcat(copy1, "\\staging");
                            char dastor[100];
                            sprintf(dastor, "copy %s %s", name[d], copy1);
                            system(dastor);
                            char *temp_dir = basename(name[d]);
                            staging = fopen(copy_staging, "a");
                            fprintf(staging, "%s\n", temp_dir);
                            fclose(staging);
                        }
                    }

                    else
                    {
                        char *temp = basename(name[d]);
                        printf("directory %s is not exists.\n", temp);
                    }
                }
            }
        }

        else if (strncmp(input, "bizhbi add depth", 16) == 0)
        {
            FILE *file;
            char line[100];
            DIR *dir;
            struct dirent *entry;
            file = fopen(copy_staging, "r");
            if (file == NULL)
                printf("Error opening file.\n");
            dir = opendir(copy_one_cu);
            if (dir == NULL)
                printf("Error opening directory.\n");

            while (fgets(line, sizeof(line), file))
            {
                line[strcspn(line, "\n")] = '\0';
                while ((entry = readdir(dir)) != NULL)
                {
                    if (strcmp(line, entry->d_name) == 0)
                    {
                        printf("Alert:%s is on stage mode\n", entry->d_name);
                        break;
                    }
                }
                rewinddir(dir);
            }
            fclose(file);
            FILE *tem = fopen(cop_depth, "w");
            while ((entry = readdir(dir)) != NULL)
            {
                if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0))
                {
                    fprintf(tem, "%s\n", entry->d_name);
                }
            }
            fclose(tem);
            closedir(dir); // for moving the pointer of pc.
            FILE *file1, *file2;
            char line1[100], line2[100];
            int matchhh = 0;

            file1 = fopen(cop_depth, "r");
            file2 = fopen(copy_staging, "r");
            while (fgets(line1, sizeof(line1), file1))
            {
                rewind(file2); // for moving the pointer of pc.
                matchhh = 0;
                while (fgets(line2, sizeof(line2), file2))
                {
                    if (strcmp(line1, line2) == 0)
                    {
                        matchhh = 1;
                        break;
                    }
                }

                if (matchhh == 0)
                {
                    line1[strcspn(line1, "\n")] = '\0';
                    printf("Alert: %s is not on stage mode.\n", line1);
                }
            }

            fclose(file1);
            fclose(file2);
            remove(file1);
            remove(tem);
        }

        else if (strncmp(input, "bizhbi reset", 12) == 0 && strcmp(input, "bizhbi reset -undo") != 0 && strncmp(input, "bizhbi reset -redo", 16) != 0)
        {
            mkdir(copy_unstage);
            char reset[200];
            saparetor(input, reset);
            // const char *filename = "staging.txt";
            struct stat path_stat;
            if (stat(reset, &path_stat) == 0)
            {
                if (S_ISDIR(path_stat.st_mode))
                {
                    reset_for_directory(copy_staging, reset);
                }
                else if (S_ISREG(path_stat.st_mode))
                {
                    char *name = basename(reset);

                    char dest[100];
                    strcpy(dest, currentDirectory);
                    strcat(dest, "\\staging\\\\");
                    strcat(dest, name);
                    // printf("%s\n", dest);
                    char dastor[100];
                    sprintf(dastor, "copy %s %s", reset, copy_unstage);
                    system(dastor);
                    char dastor2[100];
                    // sprintf(dastor2, "del \"%s\"", dest);
                    // system(dastor2);
                    remove(dest);
                    FILE *file = fopen(copy_staging, "r");
                    if (file == NULL)
                    {
                        printf("Error opening file.\n");
                        continue;
                    }
                    FILE *tempFile = fopen(file_temp, "w");
                    if (tempFile == NULL)
                    {
                        printf("Error creating temporary file.\n");
                        fclose(file);
                        continue;
                    }
                    FILE *unstaged = fopen(cop_unstage, "a");
                    if (unstaged == NULL)
                    {
                        printf("Error: cannot create unstaged file.\n");
                        fclose(tempFile);
                        fclose(file);
                        continue;
                    }

                    char line[1000];
                    while (fgets(line, sizeof(line), file) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        if (strstr(line, name) == NULL)
                        {

                            fprintf(tempFile, "%s\n", line);
                        }
                        else
                        {
                            fprintf(unstaged, "%s\n", line);
                        }
                    }
                    fclose(unstaged);
                    fclose(file);
                    fclose(tempFile);
                    remove(copy_staging);
                    rename(file_temp, copy_staging);
                    fclose(tempFile);
                }
            }
        }

        else if (strcmp(input, "bizhbi add -redo") == 0)
        {
            mkdir(copy_fstaging);
            char dest[100];
            strcpy(dest, currentDirectory);
            strcat(dest, "\\unstage");
            char stage[100];
            strcpy(stage, currentDirectory);
            strcat(stage, "\\staging");
            char dastor[100];
            sprintf(dastor, "copy %s %s", dest, stage);
            system(dastor);
            char dastor2[100];
            sprintf(dastor2, "rmdir /s /q %s", dest);
            system(dastor2);

            FILE *sourceFile, *destinationFile;
            char ch;
            sourceFile = fopen(cop_unstage, "r");
            if (sourceFile == NULL)
            {
                printf("Unable to open source file.\n");
                continue;
            }

            destinationFile = fopen(copy_staging, "a");
            if (destinationFile == NULL)
            {
                printf("Unable to open destination file.\n");
                fclose(sourceFile);
                continue;
            }

            while ((ch = fgetc(sourceFile)) != EOF)
            {
                fputc(ch, destinationFile);
            }

            fclose(sourceFile);
            fclose(destinationFile);

            printf("The mission is done.\n");
            remove(cop_unstage);
        }

        else if (strcmp(input, "bizhbi reset -undo") == 0)
        {
            mkdir(copy_unstage);
            mkdir(copy_staging);
            DIR *dir;
            struct dirent *entry;
            struct stat file_stat;
            time_t last_modified = 0;
            char last_modified_file[256];
            FILE *file = fopen(cop_unstage, "a");
            if (file == NULL)
            {
                printf("Error opening file.\n");
                continue;
            }
            FILE *tempFile = fopen(temppp, "w");
            if (tempFile == NULL)
            {
                printf("Error: creating temporary file.\n");
                fclose(tempFile);
                continue;
            }
            FILE *unstaged = fopen(copy_staging, "r");
            if (unstaged == NULL)
            {
                printf("Error: cannot create staging file.\n");
                fclose(tempFile);
                fclose(unstaged);
                continue;
            }
            dir = opendir(copy_fstaging);
            if (dir == NULL)
            {
                printf("Error opening directory\n");
                continue;
            }
            while ((entry = readdir(dir)) != NULL)
            {
                if (entry->d_name[0] == '.')
                {
                    continue;
                }
                char file_path[256];
                strcpy(file_path, currentDirectory);
                strcat(file_path, "\\staging\\\\");
                strcat(file_path, entry->d_name);
                // sprintf(file_path, "staging\\%s", entry->d_name);
                if (stat(file_path, &file_stat) == -1)
                {
                    printf("Error:getting file stats\n");
                    continue;
                }
                if (file_stat.st_mtime > last_modified)
                {
                    last_modified = file_stat.st_mtime; // finding the biggesst time.
                    strcpy(last_modified_file, entry->d_name);
                }
            }

            closedir(dir);

            printf("Last modified file in staging: %s\n", last_modified_file);
            char line[100];
            fprintf(file, "%s\n", last_modified_file);
            fclose(file);
            while (fgets(line, sizeof(line), unstaged) != NULL)
            { // staging
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, last_modified_file) == 0)
                {
                    fprintf(tempFile, "%s\n", last_modified_file);
                }
                else
                {
                    fprintf(tempFile, "%s\n", line);
                }
            }
            fclose(tempFile);
            fclose(unstaged);
            remove(copy_staging);
            rename(temppp, copy_staging);
            fclose(tempFile);

            char comman[100];
            char t[100];
            char des[100];
            strcpy(des, currentDirectory);
            strcat(des, "\\unstage");
            char cwd1[1024];
            char s[] = "\\staging\\\\";
            strcat(s, last_modified_file);
            strcpy(cwd1, currentDirectory);
            strcat(cwd1, s);
            // printf("%s", cwd1);
            sprintf(comman, "move %s %s", cwd1, des);
            system(comman);
            FILE *hi = fopen(temp_b, "a");
            FILE *uunstaged = fopen(copy_staging, "r");
            char linee[1000];
            while (fgets(linee, sizeof(linee), uunstaged) != NULL)
            {
                linee[strcspn(linee, "\n")] = '\0';
                if (strcmp(linee, last_modified_file) != 0)
                {

                    fprintf(hi, "%s\n", linee);
                }
            }
            fclose(hi);
            fclose(uunstaged);

            remove(copy_staging);
            rename(temp_b, copy_staging);
            fclose(hi);
        }

        else if (strncmp(input, "bizhbi status", 13) == 0)
        {
            DIR *dir_s;
            struct dirent *entry_s;
            char second_con[100][100];
            char temp_cond[100][100];
            int count_s = 0;
            dir_s = opendir(copy_one_cu);

            // Read each entry in the directory
            while ((entry_s = readdir(dir_s)) != NULL)
            {
                // Ignore "." and ".." entries
                if (strcmp(entry_s->d_name, ".") != 0 && strcmp(entry_s->d_name, "..") != 0)
                {
                    strcpy(second_con[count_s], entry_s->d_name);
                    count_s++;
                }
            }
            closedir(dir_s);
            int flag_for_stat_d = 0;
            for (i_s = 0; i_s < countt; i_s++)
            {
                flag_for_stat_d = 0;
                for (int j = 0; j < count_s; j++)
                {
                    if (flag_for_stat_d == 0)
                    {
                        if (strcmp(first_name_cond[i_s], second_con[j]) == 0)
                        {
                            flag_for_stat_d = 1;
                        }
                    }
                }
                if (flag_for_stat_d == 0)
                {
                    staging = fopen(copy_staging, "r");
                    char line[100];
                    int flag = 0;
                    while (fgets(line, sizeof(line), staging) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line, first_name_cond[i_s]) == 0)
                        {
                            flag = 1;
                            strcpy(temp_cond[i_s], first_name_cond[i_s]);
                            printf("%s || +D\n", first_name_cond[i_s]);
                            break;
                        }
                    }
                    fclose(staging);
                    if (flag == 0)
                    {
                        strcpy(temp_cond[i_s], first_name_cond[i_s]);
                        printf("%s || -D\n", first_name_cond[i_s]);
                    }
                }
            }
            int flag_for_stat_a = 0;
            for (int k = 0; k < count_s; k++)
            {
                flag_for_stat_a = 0;
                for (int l = 0; l < countt; l++)
                {
                    if (flag_for_stat_a == 0)
                    {
                        if (strcmp(second_con[k], first_name_cond[l]) == 0)
                        {
                            flag_for_stat_a = 1;
                        }
                    }
                }
                if (flag_for_stat_a == 0)
                {
                    staging = fopen(copy_staging, "r");
                    char line[100];
                    int flag = 0;
                    while (fgets(line, sizeof(line), staging) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line, second_con[k]) == 0)
                        {
                            flag = 1;
                            printf("%s || +A\n", second_con[k]);
                            break;
                        }
                    }
                    fclose(staging);
                    if (flag == 0)
                    {
                        printf("%s || -A\n", second_con[k]);
                    }
                }
            }
            struct stat updatedFileStat;
            time_t updatedLastModifiedTime[256];
            for (int k = 0; k < countt; k++)
            {
                stat(file_address[k], &updatedFileStat);
                updatedLastModifiedTime[k] = updatedFileStat.st_mtime;
                if ((lastModifiedTime[k] != updatedLastModifiedTime[k] && strcmp(temp_cond[k], first_name_cond[k]) != 0))
                {
                    staging = fopen(copy_staging, "r");
                    char line[100];
                    int flag = 0;
                    while (fgets(line, sizeof(line), staging) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line, first_name_cond[k]) == 0)
                        {
                            printf("%s || +M\n", first_name_cond[k]);
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0)
                    {
                        printf("%s || -M\n", first_name_cond[k]);
                    }
                }
            }
        }

        else if (strncmp(input, "bizhbi commit -m", 16) == 0)
        {
            mkdir(copy_commi);
            if (access(directoryPath, F_OK) != -1)
            {
                char commit_message[1000];
                if (strstr(input, "\"") != NULL)
                {
                    saparetor(input, commit_message);
                    int len = strlen(commit_message);
                    if (len >= 72)
                    {
                        printf("plaese enter a shorter commit.");
                        continue;
                    }
                    staging = fopen(copy_staging, "r");
                    char copy_address[500];
                    strcpy(copy_address, currentDirectory);
                    strcat(copy_address, "\\\\staging.txt");
                    fseek(staging, 0, SEEK_END);
                    long size = ftell(staging);
                    if (size == 0 || staging == NULL)
                    {
                        printf("there is no file on stage mood. first please add some file.");
                        fclose(staging);
                    }
                    else
                    {
                        char line[300];
                        FILE *message = fopen(messsage, "a");
                        // Get the current time
                        time_t currentTime = time(NULL);
                        char *timeString;
                        commit = fopen(copy_commit, "a");
                        rewind(staging);
                        int count = 0; // number of files that goes to staging.
                        while (fgets(line, sizeof(line), staging) != NULL)
                        {
                            int len = strlen(line);
                            line[len] = '\0';
                            fprintf(commit, "%s\n", line);
                            if (hasDot(line))
                                count++;
                        }
                        fclose(staging);
                        char line1[100];
                        char *ptr;
                        global_config_file = fopen(global, "r");
                        if (global_config_file != NULL)
                        {
                            while (fgets(line1, sizeof(line1), global_config_file) != NULL)
                            {
                                if (strstr(line1, "last") != NULL)
                                {
                                    char *token;
                                    token = strtok(line1, ":");
                                    token = strtok(NULL, " ");
                                    commit_id = atoi(token);
                                    commit_id++;
                                    ptr = malloc(sizeof(char) * 2);
                                    sprintf(ptr, "%d", commit_id);
                                }
                            }
                        }
                        fclose(global_config_file);
                        global_config_file = fopen(global, "r");
                        char line2[100];
                        FILE *fcommit = fopen(temp_c, "w");
                        while (fgets(line2, sizeof(line2), global_config_file) != NULL)
                        {
                            int len = strlen(line2);
                            line2[len] = '\0';

                            if (strstr(line2, "last") != NULL)
                            {
                                fprintf(fcommit, "last_commit_id : %s\n", ptr);
                            }
                            else
                            {
                                fprintf(fcommit, "%s", line2);
                            }
                        }
                        fclose(fcommit);
                        fclose(global_config_file);
                        remove(global);
                        rename(temp_c, global);
                        fclose(fcommit);
                        char line3[100];
                        staging = fopen(copy_staging, "r");
                        rewind(staging);
                        FILE *gc = fopen(global, "r");
                        char line_gc[100];
                        char *saver_user;
                        while (fgets(line_gc, sizeof(line_gc), gc) != NULL)
                        {
                            saver_user = strtok(line_gc, ":");
                            saver_user = strtok(NULL, " ");
                            break;
                        }
                        fclose(gc);
                        while (fgets(line3, sizeof(line3), staging) != NULL)
                        {
                            if (hasDot(line3))
                            {
                                fprintf(message, "file : %s", line3);
                                fprintf(message, "username : %s\n", saver_user);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_message);
                                fprintf(message, "number of files in this commit is : %d\n", count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "master");
                            }
                        }
                        fclose(commit);
                        fclose(message);
                        fclose(staging);
                        staging = fopen(copy_staging, "w");
                        fclose(staging);
                        char commit_iid[100];
                        char str[100];
                        sprintf(str, "%d", commit_id);
                        strcpy(commit_iid, currentDirectory);
                        strcat(commit_iid, "\\commit\\");
                        strcat(commit_iid, str);
                        mkdir(commit_iid);
                        char dest[100];
                        strcpy(dest, currentDirectory);
                        strcat(dest, "\\commit");
                        strcat(dest, "\\");
                        strcat(dest, str);
                        char stage[100];
                        strcpy(stage, currentDirectory);
                        strcat(stage, "\\\\staging");
                        char dastor[100];
                        sprintf(dastor, "copy %s %s", stage, dest);
                        system(dastor);
                        char dastor2[100];
                        sprintf(dastor2, "rmdir /s /q %s", stage);
                        system(dastor2);
                        /*char copy1000[100];
                        strcpy(copy1000, currentDirectory);
                        strcat(copy1000, "\\commit");
                        char dastor3[100];
                        sprintf(dastor3, "move %s %s", dest, copy1000);
                        system(dastor3);*/

                        printf("your commit id is : %d\n", commit_id);
                        printf("your commit message is :%s\n", commit_message);
                        printf("your commit time : %s", timeString);
                    }
                }
                else
                {
                    char *extract[1000];
                    int index = 0;
                    char delimeter[] = " ";
                    char *ptr = strtok(input, delimeter);
                    while (ptr != NULL)
                    {
                        extract[index] = ptr;
                        index++;
                        ptr = strtok(NULL, delimeter);
                    }
                    int len = strlen(extract[index - 1]);
                    if (strcmp(extract[index - 1], "-m") == 0)
                    {
                        printf("please enter a message.");
                        continue;
                    }
                    if (len >= 72)
                    {
                        printf("plaese enter a shorter commit.");
                        continue;
                    }
                    staging = fopen(copy_staging, "r");
                    char copy_address[500];
                    strcpy(copy_address, currentDirectory);
                    strcat(copy_address, "\\\\staging.txt");
                    fseek(staging, 0, SEEK_END);
                    long size = ftell(staging);
                    if (size == 0 || staging == NULL)
                    {
                        printf("there is no file on stage mood. first please add some file.");
                        fclose(staging);
                        continue;
                    }
                    else
                    {
                        char line[300];
                        FILE *message = fopen(messsage, "a");
                        // Get the current time
                        time_t currentTime = time(NULL);
                        char *timeString;
                        commit = fopen(copy_commit, "a");
                        rewind(staging);
                        int count = 0; // number of files that goes to staging.
                        while (fgets(line, sizeof(line), staging) != NULL)
                        {
                            // int len = strlen(line);
                            // line[len] = '\0';
                            fprintf(commit, "%s", line);
                            if (hasDot(line))
                                count++;
                        }
                        fclose(staging);
                        char line1[100];
                        char *ptr;
                        global_config_file = fopen(global, "r");
                        if (global_config_file != NULL)
                        {
                            while (fgets(line1, sizeof(line1), global_config_file) != NULL)
                            {
                                if (strstr(line1, "last") != NULL)
                                {
                                    char *token;
                                    token = strtok(line1, ":");
                                    token = strtok(NULL, " ");
                                    commit_id = atoi(token);
                                    commit_id++;
                                    ptr = malloc(sizeof(char) * 2);
                                    sprintf(ptr, "%d", commit_id);
                                }
                            }
                        }
                        fclose(global_config_file);
                        global_config_file = fopen(global, "r");
                        char line2[100];
                        FILE *fcommit = fopen(temp_c, "w");
                        while (fgets(line2, sizeof(line2), global_config_file) != NULL)
                        {
                            // int len = strlen(line2);
                            // line2[len] = '\0';
                            if (strstr(line2, "last") != NULL)
                            {
                                fprintf(fcommit, "last_commit_id : %s\n", ptr);
                            }
                            else
                            {
                                fprintf(fcommit, "%s", line2);
                            }
                        }
                        fclose(fcommit);
                        fclose(global_config_file);
                        remove(global);
                        rename(temp_c, global);
                        fclose(fcommit);
                        char line3[100];
                        FILE *gc = fopen(global, "r");
                        char line_gc[100];
                        char *saver_user;
                        while (fgets(line_gc, sizeof(line_gc), gc) != NULL)
                        {
                            saver_user = strtok(line_gc, ":");
                            saver_user = strtok(NULL, " ");
                            break;
                        }
                        fclose(gc);
                        staging = fopen(copy_staging, "r");
                        rewind(staging);
                        while (fgets(line3, sizeof(line3), staging) != NULL)
                        {
                            if (hasDot(line3))
                            {
                                fprintf(message, "file : %s", line3);
                                fprintf(message, "username : %s\n", saver_user);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", extract[index - 1]);
                                fprintf(message, "number of files in this commit is : %d\n", count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "master");
                            }
                        }
                        fclose(commit);
                        fclose(message);
                        fclose(staging);
                        staging = fopen(copy_staging, "w");
                        fclose(staging);
                        char commit_iid[100];
                        char str[100];
                        sprintf(str, "%d", commit_id);
                        strcpy(commit_iid, currentDirectory);
                        strcat(commit_iid, "\\commit\\");
                        strcat(commit_iid, str);
                        mkdir(commit_iid);
                        char dest[100];
                        strcpy(dest, currentDirectory);
                        strcat(dest, "\\commit\\");
                        strcat(dest, str);
                        char stage[100];
                        strcpy(stage, currentDirectory);
                        strcat(stage, "\\\\staging");
                        char dastor[100];
                        sprintf(dastor, "copy %s %s", stage, dest);
                        system(dastor);
                        char dastor2[100];
                        sprintf(dastor2, "rmdir /s /q %s", stage);
                        system(dastor2);
                        /* char copy1000[100];
                         strcpy(copy1000, currentDirectory);
                         strcat(copy1000, "\\commit");
                         char dastor3[100];
                         sprintf(dastor3, "move %s %s", dest, copy1000);
                         system(dastor3);*/
                        printf("your commit id is : %d\n", commit_id);
                        printf("your commit message is :%s\n", extract[index - 1]);
                        printf("your commit time : %s", timeString);
                    }
                }
            }

            else
            {
                char commit_message[1000];
                if (strstr(input, "\"") != NULL)
                {

                    saparetor(input, commit_message);
                    int len = strlen(commit_message);
                    if (len >= 72)
                    {
                        printf("plaese enter a shorter commit.");
                        continue;
                    }
                    staging = fopen(copy_staging, "r");
                    char copy_address[500];
                    strcpy(copy_address, currentDirectory);
                    strcat(copy_address, "\\\\staging.txt");
                    fseek(staging, 0, SEEK_END);
                    long size = ftell(staging);
                    if (size == 0 || staging == NULL)
                    {
                        printf("there is no file on stage mood. first please add some file.");
                        fclose(staging);
                        continue;
                    }
                    else
                    {
                        char line[300];
                        FILE *message = fopen(messsage, "a");
                        // Get the current time
                        time_t currentTime = time(NULL);
                        char *timeString;
                        commit = fopen(copy_commit, "a");
                        rewind(staging);
                        int count = 0; // number of files that goes to staging.
                        while (fgets(line, sizeof(line), staging) != NULL)
                        {
                            fputs(line, commit);
                            if (hasDot(line))
                                count++;
                        }
                        fclose(staging);
                        fclose(commit);
                        char line_user[100];
                        char *ptr;
                        char line_con[100];
                        FILE *config = fopen(copy_config, "r");
                        FILE *user = fopen(copy_info_saver, "r");
                        char *token2;
                        rewind(user);
                        rewind(config);
                        while (fgets(line_user, sizeof(line_user), user) != NULL)
                        {
                            line_user[strcspn(line_user, "\n")] = '\0';
                            if (strstr(line_user, "Username") != NULL)
                            {
                                token2 = strtok(line_user, ":");
                                token2 = strtok(NULL, " ");
                                break;
                            }
                        }
                        int count_l = 1;
                        rewind(config);
                        int saver = 0;
                        rewind(config);
                        while (fgets(line_con, sizeof(line_con), config) != NULL)
                        {
                            line_con[strlen(line_con) - 1] = '\0';
                            if ((count_l % 5 == 1))
                            {
                                char *extract;
                                extract = strtok(line_con, ":");
                                extract = strtok(NULL, " ");
                                if (strcmp(extract, token2) == 0)
                                {
                                    saver = count_l + 2;
                                }
                            }
                            if (count_l == saver)
                            {
                                char *token;
                                token = strtok(line_con, ":");
                                token = strtok(NULL, " ");
                                // printf("%s", token);
                                commit_id = atoi(token);
                                commit_id++;
                                //  printf("%d\n", commit_id);
                                ptr = malloc(sizeof(char) * 2);
                                sprintf(ptr, "%d", commit_id);
                                break;
                            }
                            count_l++;
                        }
                        fclose(config);
                        fclose(user);
                        config = fopen(copy_config, "r");
                        char line2[100];
                        FILE *fcommit = fopen(temp_c, "w");
                        int counter_c = 0;
                        while (fgets(line2, sizeof(line2), config) != NULL)
                        {
                            counter_c++;
                            if (counter_c == saver)
                            {
                                fprintf(fcommit, "last_commit_id : %s\n", ptr);
                            }
                            else
                            {
                                fprintf(fcommit, "%s", line2);
                            }
                        }
                        fclose(fcommit);
                        fclose(config);
                        remove(copy_config);
                        rename(temp_c, copy_config);
                        fclose(fcommit);
                        char line3[100];
                        staging = fopen(copy_staging, "r");
                        rewind(staging);
                        while (fgets(line3, sizeof(line3), staging) != NULL)
                        {
                            if (hasDot(line3))
                            {
                                fprintf(message, "file : %s", line3);
                                fprintf(message, "username : %s\n", token2);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_message);
                                fprintf(message, "number of files in this commit is : %d\n", count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "master");
                            }
                        }
                        fclose(commit);
                        fclose(message);
                        fclose(staging);
                        staging = fopen(copy_staging, "w");
                        fclose(staging);
                        char str[100];
                        char commit_iid[100];
                        sprintf(str, "%d", commit_id);
                        strcpy(commit_iid, currentDirectory);
                        strcat(commit_iid, "\\commit\\");
                        strcat(commit_iid, str);
                        mkdir(commit_iid);
                        char dest[100];
                        strcpy(dest, currentDirectory);
                        strcat(dest, "\\commit\\");
                        strcat(dest, str);
                        char stage[100];
                        strcpy(stage, currentDirectory);
                        strcat(stage, "\\\\staging");
                        char dastor[100];
                        sprintf(dastor, "copy %s %s", stage, dest);
                        system(dastor);
                        char dastor2[100];
                        sprintf(dastor2, "rmdir /s /q %s", stage);
                        system(dastor2);
                        /* char copy1000[100];
                         strcpy(copy1000, currentDirectory);
                         strcat(copy1000, "\\commit");
                         char dastor3[100];
                         sprintf(dastor3, "move %s %s", dest, copy1000);
                         system(dastor3);*/
                        printf("the user committing project is: %s\n", token2);
                        printf("your commit id is : %d\n", commit_id);
                        printf("your commit message is :%s\n", commit_message);
                        printf("your commit time : %s", timeString);
                    }
                }
                else
                {

                    char saved[100];
                    char *extract[1000];
                    int index = 0;
                    char delimeter[] = " ";
                    char *ptr = strtok(input, delimeter);
                    while (ptr != NULL)
                    {
                        extract[index] = ptr;
                        index++;
                        ptr = strtok(NULL, delimeter);
                    }
                    strcpy(commit_message, extract[index - 1]);
                    int len = strlen(commit_message);
                    if (strcmp(extract[index - 1], "-m") == 0)
                    {
                        printf("please enter a message.");
                        continue;
                    }
                    if (len >= 72)
                    {
                        printf("plaese enter a shorter commit.");
                        continue;
                    }
                    staging = fopen(copy_staging, "r");
                    char copy_address[500];
                    strcpy(copy_address, currentDirectory);
                    strcat(copy_address, "\\\\staging.txt");
                    fseek(staging, 0, SEEK_END);
                    long size = ftell(staging);
                    if (size == 0 || staging == NULL)
                    {
                        printf("there is no file on stage mood. first please add some file.");
                        fclose(staging);
                        continue;
                    }
                    else
                    {
                        char line[300];
                        FILE *message = fopen(messsage, "a");
                        // Get the current time
                        time_t currentTime = time(NULL);
                        char *timeString;
                        commit = fopen(copy_commit, "a");
                        rewind(staging);
                        int count = 0; // number of files that goes to staging.
                        while (fgets(line, sizeof(line), staging) != NULL)
                        {
                            fputs(line, commit);
                            if (hasDot(line))
                                count++;
                        }
                        fclose(staging);
                        fclose(commit);
                        char line_user[100];
                        char *ptr;
                        char line_con[100];
                        FILE *config = fopen(copy_config, "r");
                        FILE *user = fopen(copy_info_saver, "r");
                        char *token2;
                        rewind(user);
                        rewind(config);
                        while (fgets(line_user, sizeof(line_user), user) != NULL)
                        {
                            line_user[strcspn(line_user, "\n")] = '\0';
                            if (strstr(line_user, "Username") != NULL)
                            {
                                token2 = strtok(line_user, ":");
                                token2 = strtok(NULL, " ");
                                break;
                            }
                        }
                        int count_l = 1;
                        rewind(config);
                        int saver = 0;
                        rewind(config);
                        while (fgets(line_con, sizeof(line_con), config) != NULL)
                        {
                            line_con[strlen(line_con) - 1] = '\0';
                            if ((count_l % 5 == 1))
                            {
                                char *extract;
                                extract = strtok(line_con, ":");
                                extract = strtok(NULL, " ");
                                if (strcmp(extract, token2) == 0)
                                {
                                    saver = count_l + 2;
                                }
                            }
                            if (count_l == saver)
                            {
                                char *token;
                                token = strtok(line_con, ":");
                                token = strtok(NULL, " ");
                                // printf("%s", token);
                                commit_id = atoi(token);
                                commit_id++;
                                //  printf("%d\n", commit_id);
                                ptr = malloc(sizeof(char) * 2);
                                sprintf(ptr, "%d", commit_id);
                                break;
                            }
                            count_l++;
                        }
                        fclose(config);
                        fclose(user);
                        config = fopen(copy_config, "r");
                        char line2[100];
                        FILE *fcommit = fopen(temp_c, "w");
                        int counter_c = 0;
                        while (fgets(line2, sizeof(line2), config) != NULL)
                        {
                            counter_c++;
                            if (counter_c == saver)
                            {
                                fprintf(fcommit, "last_commit_id : %s\n", ptr);
                            }
                            else
                            {
                                fprintf(fcommit, "%s", line2);
                            }
                        }
                        fclose(fcommit);
                        fclose(config);
                        remove(copy_config);
                        rename(temp_c, copy_config);
                        fclose(fcommit);
                        char line3[100];
                        staging = fopen(copy_staging, "r");
                        rewind(staging);
                        while (fgets(line3, sizeof(line3), staging) != NULL)
                        {
                            if (hasDot(line3))
                            {
                                fprintf(message, "file : %s", line3);
                                fprintf(message, "username : %s\n", token2);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_message);
                                fprintf(message, "number of files in this commit is : %d\n", count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "master");
                            }
                        }
                        fclose(commit);
                        fclose(message);
                        fclose(staging);
                        staging = fopen(copy_staging, "w");
                        fclose(staging);
                        char str[100];
                        char commit_iid[100];
                        sprintf(str, "%d", commit_id);
                        strcpy(commit_iid, currentDirectory);
                        strcat(commit_iid, "\\commit\\");
                        strcat(commit_iid, str);
                        mkdir(commit_iid);

                        char dest[100];
                        strcpy(dest, currentDirectory);
                        strcat(dest, "\\commit\\");
                        strcat(dest, str);
                        char stage[100];
                        strcpy(stage, currentDirectory);
                        strcat(stage, "\\\\staging");
                        char dastor[100];
                        sprintf(dastor, "copy %s %s", stage, dest);
                        system(dastor);
                        char dastor2[100];
                        sprintf(dastor2, "rmdir /s /q %s", stage);
                        system(dastor2);
                        /* char copy1000[100];
                         strcpy(copy1000, currentDirectory);
                         strcat(copy1000, "\\commit");
                         char dastor3[100];
                         sprintf(dastor3, "move %s %s", dest, copy1000);
                         system(dastor3);*/

                        printf("the user committing project is: %s\n", token2);
                        printf("your commit id is : %d\n", commit_id);
                        printf("your commit message is :%s\n", commit_message);
                        printf("your commit time : %s", timeString);
                    }
                }
            }
        }

        else if (strncmp(input, "bizhbi set -m", 13) == 0)
        {
            FILE *shortcuts = fopen(shortt, "a");
            extractText(input, shortcut_message);
            // printf("%s",shortcut_message);
            char *extract[1000];
            int index = 0;
            char delimeter[] = " ";
            char *ptr = strtok(input, delimeter);
            while (ptr != NULL)
            {
                extract[index] = ptr;
                index++;
                ptr = strtok(NULL, delimeter);
            }
            strcpy(shortcut, extract[index - 1]);

            fprintf(shortcuts, "%s\n", shortcut);
            fprintf(shortcuts, "%s\n", shortcut_message);
            fclose(shortcuts);
        }

        else if (strncmp(input, "bizhbi commit -s", 16) == 0)
        {
            char *extract_1[1000];
            int index_1 = 0;
            char delimeter[] = " ";
            char *ptr = strtok(input, delimeter);
            while (ptr != NULL)
            {
                extract_1[index_1] = ptr;
                index_1++;
                ptr = strtok(NULL, delimeter);
            }
            char line[100];
            int flag_for_commit = 0;
            FILE *shorts = fopen(shortt, "r");
            rewind(shorts);
            while (fgets(line, sizeof(line), shorts) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, extract_1[index_1 - 1]) == 0)
                {
                    flag_for_commit = 1;
                    if (access(directoryPath, F_OK) != -1)
                    {
                        char commit_message[1000];
                        strcpy(commit_message, extract_1[index_1 - 1]);
                        int len = strlen(commit_message);
                        if (strcmp(extract_1[index_1 - 1], "-m") == 0)
                        {
                            printf("please enter a message.");
                            continue;
                        }
                        if (len >= 72)
                        {
                            printf("plaese enter a shorter commit.");
                            continue;
                        }
                        staging = fopen(copy_staging, "r");
                        char copy_address[500];
                        strcpy(copy_address, currentDirectory);
                        strcat(copy_address, "\\\\staging.txt");
                        fseek(staging, 0, SEEK_END);
                        long size = ftell(staging);
                        if (size == 0 || staging == NULL)
                        {
                            printf("there is no file on stage mood. first please add some file.");
                            fclose(staging);
                            continue;
                        }
                        else
                        {
                            strcpy(commit_message, extract_1[index_1 - 1]);
                            int len = strlen(commit_message);
                            if (strcmp(extract_1[index_1 - 1], "-m") == 0)
                            {
                                printf("please enter a message.");
                                fclose(staging);
                                continue;
                            }
                            if (len >= 72)
                            {
                                printf("plaese enter a shorter commit.");
                                fclose(staging);
                                continue;
                            }
                            fclose(staging);
                            staging = fopen(copy_staging, "r");
                            char copy_address[500];
                            strcpy(copy_address, currentDirectory);
                            strcat(copy_address, "\\\\staging.txt");
                            fseek(staging, 0, SEEK_END);
                            long size = ftell(staging);
                            if (size == 0 || staging == NULL)
                            {
                                printf("there is no file on stage mood. first please add some file.");
                                fclose(staging);
                                continue;
                            }
                            else
                            {
                                char line[300];
                                FILE *message = fopen(messsage, "a");
                                // Get the current time
                                time_t currentTime = time(NULL);
                                char *timeString;
                                commit = fopen(copy_commit, "a");
                                rewind(staging);
                                int count = 0; // number of files that goes to staging.
                                while (fgets(line, sizeof(line), staging) != NULL)
                                {
                                    fprintf(commit, "%s", line);
                                    if (hasDot(line))
                                        count++;
                                }
                                fclose(staging);
                                char line1[100];
                                char *ptr;
                                global_config_file = fopen(global, "r");
                                if (global_config_file != NULL)
                                {
                                    while (fgets(line1, sizeof(line1), global_config_file) != NULL)
                                    {
                                        if (strstr(line1, "last") != NULL)
                                        {
                                            char *token;
                                            token = strtok(line1, ":");
                                            token = strtok(NULL, " ");
                                            commit_id = atoi(token);
                                            commit_id++;
                                            ptr = malloc(sizeof(char) * 2);
                                            sprintf(ptr, "%d", commit_id);
                                        }
                                    }
                                }
                                fclose(global_config_file);
                                global_config_file = fopen(global, "r");
                                char line2[100];
                                FILE *fcommit = fopen(temp_c, "w");
                                while (fgets(line2, sizeof(line2), global_config_file) != NULL)
                                {
                                    if (strstr(line2, "last") != NULL)
                                    {
                                        fprintf(fcommit, "last_commit_id : %s\n", ptr);
                                    }
                                    else
                                    {
                                        fprintf(fcommit, "%s", line2);
                                    }
                                }
                                fclose(fcommit);
                                fclose(global_config_file);
                                remove(global);
                                rename(temp_c, global);
                                fclose(fcommit);
                                char line3[100];
                                FILE *gc = fopen(global, "r");
                                char line_gc[100];
                                char *saver_user;
                                while (fgets(line_gc, sizeof(line_gc), gc) != NULL)
                                {
                                    saver_user = strtok(line_gc, ":");
                                    saver_user = strtok(NULL, " ");
                                    break;
                                }
                                fclose(gc);
                                staging = fopen(copy_staging, "r");
                                rewind(staging);
                                int co = 0;
                                int check = 0;
                                char line18[100];
                                char commit_n[100];
                                FILE *sh = fopen(shortt, "r");
                                while (fgets(line18, sizeof(line18), sh) != NULL)
                                {
                                    co++;
                                    line18[strcspn(line18, "\n")] = '\0';
                                    if (strcmp(line18, commit_message) == 0)
                                    {
                                        check = co + 1;
                                    }
                                    if (check == co)
                                    {
                                        strcpy(commit_n, line18);
                                        break;
                                    }
                                }
                                fclose(sh);
                                while (fgets(line3, sizeof(line3), staging) != NULL)
                                {
                                    fprintf(message, "file : %s", line3);
                                    fprintf(message, "username : %s\n", saver_user);
                                    fprintf(message, "commit id : %d\n ", commit_id);
                                    fprintf(message, "message is : %s\n", commit_n);
                                    fprintf(message, "number of files in this commit is : %d\n", count);
                                    timeString = ctime(&currentTime);
                                    fprintf(message, "time : %s", timeString);
                                    fprintf(message, "branch : %s\n", "master");
                                }
                                fclose(commit);
                                fclose(message);
                                fclose(staging);
                                staging = fopen(copy_staging, "w");
                                fclose(staging);
                                removeSpaces(commit_n);
                                char commit_iid[100];
                                char str[100];
                                sprintf(str, "%d", commit_id);
                                strcpy(commit_iid, currentDirectory);
                                strcat(commit_iid, "\\commit\\");
                                strcat(commit_iid, str);
                                mkdir(commit_iid);
                                char dest[100];
                                strcpy(dest, currentDirectory);
                                strcat(dest, "\\commit\\");
                                strcat(dest, str);
                                char stage[100];
                                strcpy(stage, currentDirectory);
                                strcat(stage, "\\\\staging");
                                char dastor[100];
                                sprintf(dastor, "copy %s %s", stage, dest);
                                system(dastor);
                                char dastor2[100];
                                sprintf(dastor2, "rmdir /s /q %s", stage);
                                system(dastor2);
                                /*char copy1000[100];
                                strcpy(copy1000, currentDirectory);
                                strcat(copy1000, "\\commit");
                                char dastor3[100];
                                sprintf(dastor3, "move %s %s", dest, copy1000);
                                system(dastor3);*/

                                printf("your commit id is : %d\n", commit_id);
                                printf("your commit message is :%s\n", commit_n);
                                printf("your commit time : %s", timeString);
                            }
                        }
                    }

                    else
                    {
                        char commit_message[1000];
                        strcpy(commit_message, extract_1[index_1 - 1]);
                        int len = strlen(commit_message);
                        if (strcmp(extract_1[index_1 - 1], "-m") == 0)
                        {
                            printf("please enter a message.");
                            continue;
                        }
                        if (len >= 72)
                        {
                            printf("plaese enter a shorter commit.");
                            continue;
                        }
                        staging = fopen(copy_staging, "r");
                        char copy_address[500];
                        strcpy(copy_address, currentDirectory);
                        strcat(copy_address, "\\\\staging.txt");
                        fseek(staging, 0, SEEK_END);
                        long size = ftell(staging);
                        if (size == 0 || staging == NULL)
                        {
                            printf("there is no file on stage mood. first please add some file.");
                            fclose(staging);
                            continue;
                        }
                        else
                        {
                            char line[300];
                            FILE *message = fopen(messsage, "a");
                            // Get the current time
                            time_t currentTime = time(NULL);
                            char *timeString;
                            commit = fopen(copy_commit, "a");
                            rewind(staging);
                            int count = 0; // number of files that goes to staging.
                            while (fgets(line, sizeof(line), staging) != NULL)
                            {
                                fputs(line, commit);
                                if (hasDot(line))
                                    count++;
                            }
                            fclose(staging);
                            fclose(commit);
                            char line_user[100];
                            char *ptr;
                            char line_con[100];
                            FILE *config = fopen(copy_config, "r");
                            FILE *user = fopen(copy_info_saver, "r");
                            char *token2;
                            rewind(user);
                            rewind(config);
                            while (fgets(line_user, sizeof(line_user), user) != NULL)
                            {
                                line_user[strcspn(line_user, "\n")] = '\0';
                                if (strstr(line_user, "Username") != NULL)
                                {
                                    token2 = strtok(line_user, ":");
                                    token2 = strtok(NULL, " ");
                                    break;
                                }
                            }
                            int count_l = 1;
                            rewind(config);
                            int saver = 0;
                            rewind(config);
                            while (fgets(line_con, sizeof(line_con), config) != NULL)
                            {
                                line_con[strlen(line_con) - 1] = '\0';
                                if ((count_l % 5 == 1))
                                {
                                    char *extract;
                                    extract = strtok(line_con, ":");
                                    extract = strtok(NULL, " ");
                                    if (strcmp(extract, token2) == 0)
                                    {
                                        saver = count_l + 2;
                                    }
                                }
                                if (count_l == saver)
                                {
                                    char *token;
                                    token = strtok(line_con, ":");
                                    token = strtok(NULL, " ");
                                    commit_id = atoi(token);
                                    commit_id++;
                                    ptr = malloc(sizeof(char) * 2);
                                    sprintf(ptr, "%d", commit_id);
                                    break;
                                }
                                count_l++;
                            }
                            fclose(config);
                            fclose(user);
                            config = fopen(copy_config, "r");
                            char line2[100];
                            FILE *fcommit = fopen(temp_c, "w");
                            int counter_c = 0;
                            while (fgets(line2, sizeof(line2), config) != NULL)
                            {
                                counter_c++;
                                if (counter_c == saver)
                                {
                                    fprintf(fcommit, "last_commit_id : %s\n", ptr);
                                }
                                else
                                {
                                    fprintf(fcommit, "%s", line2);
                                }
                            }
                            fclose(fcommit);
                            fclose(config);
                            remove(copy_config);
                            rename(temp_c, copy_config);
                            fclose(fcommit);
                            char line3[100];
                            int co = 0;
                            int check = 0;
                            char line18[100];
                            char commit_n[100];
                            FILE *sh = fopen(shortt, "r");
                            while (fgets(line18, sizeof(line18), sh) != NULL)
                            {
                                co++;
                                line18[strcspn(line18, "\n")] = '\0';
                                if (strcmp(line18, commit_message) == 0)
                                {

                                    check = co + 1;
                                }
                                if (check == co)
                                {
                                    strcpy(commit_n, line18);
                                    break;
                                }
                            }
                            fclose(sh);
                            staging = fopen(copy_staging, "r");
                            rewind(staging);
                            while (fgets(line3, sizeof(line3), staging) != NULL)
                            {
                                fprintf(message, "file : %s", line3);
                                fprintf(message, "username : %s\n", token2);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_n);
                                fprintf(message, "number of files in this commit is : %d\n", count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "matser");
                            }
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen(copy_staging, "w");
                            fclose(staging);
                            char commit_iid[100];
                            char str[100];
                            sprintf(str, "%d", commit_id);
                            strcpy(commit_iid, currentDirectory);
                            strcat(commit_iid, "\\commit\\");
                            strcat(commit_iid, str);
                            mkdir(commit_iid);
                            char dest[100];
                            strcpy(dest, currentDirectory);
                            strcat(dest, "\\commit\\");
                            strcat(dest, str);
                            char stage[100];
                            strcpy(stage, currentDirectory);
                            strcat(stage, "\\\\staging");
                            char dastor[100];
                            sprintf(dastor, "copy %s %s", stage, dest);
                            system(dastor);
                            char dastor2[100];
                            sprintf(dastor2, "rmdir /s /q %s", stage);
                            system(dastor2);
                            /*char copy1000[100];
                            strcpy(copy1000, currentDirectory);
                            strcat(copy1000, "\\commit");
                            char dastor3[100];
                            sprintf(dastor3, "move %s %s", dest, copy1000);
                            system(dastor3);*/
                            flag_for_commit = 1; // nooooooot sure check it
                            printf("the user committing project is: %s\n", token2);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", commit_n);
                            printf("your commit time : %s", timeString);
                        }
                    }
                }
            }
            if (flag_for_commit == 0)
            {
                printf("you enterd invalid shortcut.");
            }
            fclose(shorts);
        }

        else if (strncmp(input, "bizhbi replace -m", 17) == 0)
        {
            char saved[100];
            extractText(input, saved);
            char *extract[1000];
            int index = 0;
            char delimeter[] = " ";
            char *ptr = strtok(input, delimeter);
            while (ptr != NULL)
            {
                extract[index] = ptr;
                index++;
                ptr = strtok(NULL, delimeter);
            }
            FILE *cf = fopen(temp_shortt, "w");
            FILE *ct = fopen(shortt, "r");
            int number = 1;
            char line[100];
            int flag_for_replace = 0;
            while (fgets(line, sizeof(line), ct) != NULL)
            {
                // printf("%d\n",number);
                number++;
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, extract[index - 1]) == 0)
                {
                    flag_for_replace = 1;
                    break;
                }
            }
            if (flag_for_replace == 0)
            {
                printf("please enter valid shortcut.");
                continue;
            }
            // printf("%d",number);
            fclose(ct);
            fclose(cf);
            ct = fopen(shortt, "r");
            cf = fopen(temp_shortt, "w");
            int number2 = 1;
            while (fgets(line, sizeof(line), ct) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (number2 == number)
                {
                    fprintf(cf, "%s\n", saved);
                }
                else
                {
                    fprintf(cf, "%s\n", line);
                }
                number2++;
            }
            fclose(ct);
            fclose(cf);
            remove(shortt);
            rename(temp_shortt, shortt);
            fclose(cf);
        }

        else if (strncmp(input, "bizhbi remove -s", 16) == 0)
        {
            char *extract[1000];
            int index = 0;
            char delimeter[] = " ";
            char *ptr = strtok(input, delimeter);
            while (ptr != NULL)
            {
                extract[index] = ptr;
                index++;
                ptr = strtok(NULL, delimeter);
            }
            FILE *sh = fopen(shortt, "r");
            FILE *delet = fopen(remoov, "w");
            char line[100];
            int flag_for_delet = 0;
            int number = 1;
            while (fgets(line, sizeof(line), sh) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, extract[index - 1]) == 0)
                {
                    flag_for_delet = 1;
                    break;
                }
                number++;
            }
            if (flag_for_delet == 0)
            {
                printf("please enter valid shortcut.");
                continue;
            }
            // printf("%d",number);
            fclose(sh);
            sh = fopen(shortt, "r");
            int flag_n = 0;
            int number2 = 1;
            while (fgets(line, sizeof(line), sh) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (flag_n == 1)
                {
                    flag_n = 0;
                    continue;
                }
                if (number2 == number)
                {
                    flag_n = 1;
                    continue;
                }
                else
                {
                    fprintf(delet, "%s\n", line);
                }
                number2++;
            }
            fclose(delet);
            fclose(sh);
            remove(shortt);
            rename(remoov, shortt);
            fclose(delet);
        }

        else if (strcmp("bizhbi log", input) == 0)
        {
            FILE *message = fopen(messsage, "r");
            printSentencesInReverseOrder(message);
            fclose(message);
        }

        else if (strncmp("bizhbi log -n", input, 13) == 0)
        {
            char number[100];
            char line[100];
            saparetor(input, number);
            int count = atoi(number);
            FILE *message = fopen(messsage, "r");
            reverseForLog(message, count);
            fclose(message);
        }

        else if (strncmp("bizhbi log -author", input, 18) == 0)
        {
            char user_name[200];
            saparetor(input, user_name);
            user_name[strlen(user_name)] = '\0';
            FILE *message = fopen(messsage, "r");
            ReverseFile(message);
            fclose(message);
            FILE *temp_log = fopen(temp_loog, "r");
            int log = 0;
            int check = 0;
            char line2[100];
            char *extract;
            while (fgets(line2, sizeof(line2), temp_log) != NULL)
            {
                log++;
                if (log % 7 == 6)
                {
                    extract = strtok(line2, ":");
                    extract = strtok(NULL, " ");
                    extract[strcspn(extract, "\n")] = '\0';
                    if (strcmp(user_name, extract) == 0)
                    {
                        // printf("yes");
                        check = log + 1;
                    }
                }
                if (check == log)
                {
                    char *ex;
                    ex = strtok(line2, ":");
                    ex = strtok(NULL, " ");
                    printf("%s was commited by %s\n", ex, user_name);
                }
            }
            fclose(temp_log);
        }

        else if (strncmp("bizhbi log -since", input, 17) == 0)
        {
            char time[100];
            char *token;
            saparetor(input, time);
            char line3[100];
            char *extract[100];
            int line_c = 0;
            int index = 0;
            char delimeter[] = " ";
            FILE *temp_log = fopen(temp_loog, "r");
            while (fgets(line3, sizeof(line3), temp_log) != NULL)
            {
                line_c++;
                if (line_c % 7 == 2)
                {
                    char *ptr = strtok(line3, delimeter);
                    while (ptr != NULL)
                    {
                        extract[index] = ptr;
                        index++;
                        ptr = strtok(NULL, delimeter);
                    }
                    if (compareTimes(extract[index - 2], time))
                    {
                        printf("%s - %s - %s\n", extract[index - 4], extract[index - 3], extract[index - 2]);
                    }
                }
            }
            fclose(temp_log);
        }

        else if (strncmp("bizhbi log -before", input, 18) == 0)
        {
            char time[100];
            char *token;
            saparetor(input, time);
            char line3[100];
            char *extract[100];
            int line_c = 0;
            int index = 0;
            char delimeter[] = " ";
            FILE *temp_log = fopen(temp_loog, "r");
            while (fgets(line3, sizeof(line3), temp_log) != NULL)
            {
                line_c++;
                if (line_c % 7 == 2)
                {
                    char *ptr = strtok(line3, delimeter);
                    while (ptr != NULL)
                    {
                        extract[index] = ptr;
                        index++;
                        ptr = strtok(NULL, delimeter);
                    }
                    if (compareTimes2(extract[index - 2], time))
                    {
                        printf("%s - %s - %s\n", extract[index - 4], extract[index - 3], extract[index - 2]);
                    }
                }
            }
        }

        else if (strcmp("bizhbi list branch", input) == 0)
        {
            char line[100];
            branch = fopen(copy_branch, "r");
            while (fgets(line, sizeof(line), branch) != NULL)
            {
                printf("%s", line);
            }
            fclose(branch);
        }

        else if (strncmp("bizhbi branch", input, 13) == 0)
        {
            char branch_name[100];
            saparetor(input, branch_name);
            mkdir(copy10);
            FILE *ch = fopen(copy_branch, "r");
            char line0[100];
            int flag_branch = 0;
            while (fgets(line0, sizeof(line0), ch) != NULL)
            {
                line0[strcspn(line0, "\n")] = '\0';
                if (strcmp(line0, branch_name) == 0)
                {
                    flag_branch = 1;
                    break;
                }
            }
            fclose(ch);
            if (flag_branch == 0)
            {
                char plo[100];
                strcpy(plo, currentDirectory);
                strcat(plo, "\\");
                strcat(plo, branch_name);
                mkdir(plo);
                FILE *branch = fopen(copy_branch, "a");
                fprintf(branch, "%s\n", branch_name);
                fclose(branch);
                FILE *m = fopen(messsage, "r");
                char line_m[100];
                int line_counter = 0;
                // while counts 1 more line wo we started from 0.
                while (fgets(line_m, sizeof(line_m), m) != NULL)
                {
                    line_counter++;
                }
                fclose(m);
                FILE *log = fopen(temp_loog, "r");
                char line_t[100];
                int counter_t = 1;
                int num;
                while (fgets(line_t, sizeof(line_t), log) != NULL)
                {

                    if (counter_t == 3)
                    {
                        char *number;
                        number = strtok(line_t, ":");
                        number = strtok(NULL, " ");
                        num = atoi(number);
                        break;
                    }
                    counter_t++;
                }
                m = fopen(messsage, "r");
                FILE *temp = fopen(temp_b, "w");
                char line9[100];
                int co_temp = 1;
                int sum = line_counter - (7 * num);
                for (int i = 1; i <= num; i++)
                {
                    sum = sum + 7;
                    while (fgets(line9, sizeof(line9), m) != NULL)
                    {
                        if (co_temp == sum)
                        {
                            fprintf(temp, "branch : %s\n", branch_name);
                            co_temp++;
                            break;
                        }
                        else
                        {
                            fprintf(temp, "%s", line9);
                        }
                        co_temp++;
                    }
                }

                fclose(temp);
                fclose(m);

                remove(messsage);
                rename(temp_b, messsage);
                fclose(temp);
                m = fopen(messsage, "r");
                ReverseFile(m);
                fclose(m);
                DIR *dir;
                char copy_c[100];
                strcpy(copy_c, currentDirectory);
                strcat(copy_c, "\\commit");
                char copy_com[100];
                strcpy(copy_com, copy_c);
                strcat(copy_com, "\\*");
                struct dirent *entry;
                struct stat fileStat;
                WIN32_FIND_DATA findFileData;
                HANDLE hFind = FindFirstFile(_T(copy_com), &findFileData);

                if (hFind == INVALID_HANDLE_VALUE)
                {
                    _tprintf(_T("Error opening directory\n"));
                    return 1;
                }

                FILETIME latestTime = findFileData.ftCreationTime;
                TCHAR latestFolder[MAX_PATH];
                _tcscpy(latestFolder, findFileData.cFileName);

                while (FindNextFile(hFind, &findFileData) != 0)
                {
                    if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    {
                        if (CompareFileTime(&findFileData.ftCreationTime, &latestTime) > 0)
                        {
                            latestTime = findFileData.ftCreationTime;
                            _tcscpy(latestFolder, findFileData.cFileName);
                        }
                    }
                }

                FindClose(hFind);

                _tprintf(_T("Latest folder: %s\n"), latestFolder);
                strcat(copy_c, "\\");
                strcat(copy_c, latestFolder);
                char b[100];
                char dost[100];
                char comm[100];
                strcpy(b, currentDirectory);
                strcat(b, "\\");
                strcat(b, branch_name);
                sprintf(dost, "copy %s %s", copy_c, b);
                system(dost);
                char addres_main_branch[100];
                strcpy(addres_main_branch, currentDirectory);
                strcat(addres_main_branch, "\\branch");
                sprintf(comm, "move /Y \"%s\" \"%s\"", b, addres_main_branch);
                system(comm);
                head = fopen(copy_head, "a");
                fprintf(head, "%s\n", branch_name);
                fprintf(head, "%s\n", latestFolder);
                fclose(head);
            }

            else
            {
                char plo[100];
                strcpy(plo, currentDirectory);
                strcat(plo, "\\");
                strcat(plo, branch_name);
                FILE *branch = fopen(copy_branch, "a");
                fprintf(branch, "%s\n", branch_name);
                fclose(branch);
                FILE *m = fopen(messsage, "r");
                char line_m[100];
                int line_counter = 0;
                // while counts 1 more line wo we started from 0.
                while (fgets(line_m, sizeof(line_m), m) != NULL)
                {
                    line_counter++;
                }
                fclose(m);
                FILE *log = fopen(temp_loog, "r");
                char line_t[100];
                int counter_t = 1;
                int num;
                while (fgets(line_t, sizeof(line_t), log) != NULL)
                {

                    if (counter_t == 3)
                    {
                        char *number;
                        number = strtok(line_t, ":");
                        number = strtok(NULL, " ");
                        num = atoi(number);
                        break;
                    }
                    counter_t++;
                }
                m = fopen(messsage, "r");
                FILE *temp = fopen(temp_b, "w");
                char line9[100];
                int co_temp = 1;
                int sum = line_counter - (7 * num);
                for (int i = 1; i <= num; i++)
                {
                    sum = sum + 7;
                    while (fgets(line9, sizeof(line9), m) != NULL)
                    {
                        if (co_temp == sum)
                        {
                            fprintf(temp, "branch : %s\n", branch_name);
                            co_temp++;
                            break;
                        }
                        else
                        {
                            fprintf(temp, "%s", line9);
                        }
                        co_temp++;
                    }
                }

                fclose(temp);
                fclose(m);

                remove(messsage);
                rename(temp_b, messsage);
                fclose(temp);
                m = fopen(messsage, "r");
                ReverseFile(m);
                fclose(m);
                DIR *dir;
                char copy_c[100];
                strcpy(copy_c, currentDirectory);
                strcat(copy_c, "\\commit"); // "F:\GitHub\FOP-Project-Git\output\bizhbi\commit"
                char copy_com[100];
                strcpy(copy_com, copy_c);
                strcat(copy_com, "\\*");
                struct dirent *entry;
                struct stat fileStat;
                WIN32_FIND_DATA findFileData;
                HANDLE hFind = FindFirstFile(_T(copy_com), &findFileData);

                if (hFind == INVALID_HANDLE_VALUE)
                {
                    _tprintf(_T("Error opening directory\n"));
                    return 1;
                }

                FILETIME latestTime = findFileData.ftCreationTime;
                TCHAR latestFolder[MAX_PATH];
                _tcscpy(latestFolder, findFileData.cFileName);

                while (FindNextFile(hFind, &findFileData) != 0)
                {
                    if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    {
                        if (CompareFileTime(&findFileData.ftCreationTime, &latestTime) > 0)
                        {
                            latestTime = findFileData.ftCreationTime;
                            _tcscpy(latestFolder, findFileData.cFileName);
                        }
                    }
                }

                FindClose(hFind);

                _tprintf(_T("Latest folder: %s\n"), latestFolder);
                strcat(copy_c, "\\");
                strcat(copy_c, latestFolder);
                char b[100];
                char dost[100];
                strcpy(b, currentDirectory);
                strcat(b, "\\branch\\");
                strcat(b, branch_name);
                sprintf(dost, "copy %s %s", copy_c, b);
                system(dost);
                // char line_s[100];
                // FILE* head_t = fopen(copy_head,"a");
                // FILE* fptr = fopen(temp_f,"w");
                // int ch =0;
                // int line=1;
                // while (fgets(line_s, sizeof(line_s), head_t) != NULL){
                //     line_s[strcspn(line_s,"\n")]='\0';
                //     if (strcmp(line_s,branch_name)==0){
                //         ch = line+1;
                //     }
                //     if (line==ch){
                //         fprintf(fptr,"%s\n",latestFolder);
                //     }
                //     else {
                //         fprintf(fptr,"%s",line_s);
                //     }
                //     line++;
                // }

                // fclose(head_t);
                // fclose(fptr);
                // remove(copy_head);
                // rename (temp_f,copy_head);
                // fclose(fptr);
            }
        }

        else if (strncmp("bizhbi log -branch", input, 18) == 0)
        {
            char branch_name[100];
            saparetor(input, branch_name);
            FILE *branch = fopen(copy_branch, "r");
            char line[100];
            int flag = 0;
            while (fgets(line, sizeof(line), branch) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, branch_name) == 0)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 0)
            {
                printf("Error: the branch name is invalid.\n");
                continue;
            }
            fclose(branch);
            FILE *temp_log = fopen(temp_loog, "r");
            char line1[100];
            int log = 1;
            int flag2 = 0;
            // int cou =0;
            while (fgets(line1, sizeof(line1), temp_log) != NULL)
            {

                if (log % 7 == 1)
                {
                    flag2 = 0;
                    char *token;
                    char *line_copy = (char *)malloc(100 * sizeof(char));
                    strcpy(line_copy, line1);
                    token = strtok(line_copy, ":");
                    token = strtok(NULL, " ");
                    token[strcspn(token, "\n\r")] = '\0';
                    branch_name[strcspn(branch_name, "\n\r")] = '\0';
                    if (strcmp(token, branch_name) == 0)
                    {
                        // printf("%d",log);
                        flag2 = 1;
                    }
                }
                if (flag2 == 1)
                {
                    printf("%s", line1);
                    // cou++;
                }
                // if (cou==7){
                //     cou=0;
                //     flag2=0;
                // }
                log++;
            }

            fclose(temp_log);
        }

        else if (strncmp("bizhbi log -saparetor", input, 18) == 0)
        {
            char hint[100];
            saparetor(input, hint);
            int saver[100];
            char *file_name = temp_loog;
            saparetorWordInFile(file_name, hint, saver);
            FILE *log = fopen(temp_loog, "r");
            char line[100];
            int liner = 1;
            int index = 0;
            int flag = 0;
            int c = 1;
            while (fgets(line, sizeof(line), log) != NULL)
            {
                if (liner == (saver[index]) - 3)
                {
                    flag = 1;
                    index++;
                }
                if (flag == 1 && c <= 7)
                {
                    c++;
                }
                if (flag == 1 && c > 7)
                {
                    flag = 0;
                    c = 1;
                }
                liner++;
            }
            fclose(log);
        }

        else if (strncmp("bizhbi checkout", input, 15) == 0 && strncmp("bizhbi checkout -id", input, 17) != 0 && strcmp("bizhbi checkout HEAD", input) != 0)
        {
            char branch_name[100];
            saparetor(input, branch_name);
            FILE *branch = fopen(copy_branch, "r");
            char line[100];
            int flag = 0;
            while (fgets(line, sizeof(line), branch) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, branch_name) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                printf("Error: the branch name is invalid.\n");
                continue;
            }
            fclose(branch);
            char copy_un[100];
            strcpy(copy_un, currentDirectory);
            strcat(copy_un, "\\unstage");
            struct stat st;
            if (access(copy_un, F_OK) == -1 || st.st_size == 0)
            {

                char copy_s[100];
                strcpy(copy_s, currentDirectory);
                strcat(copy_s, "\\branch\\");
                strcat(copy_s, branch_name);
                if (access(copy_s, F_OK) == -1)
                    printf("we dont have such a directory.");
                else
                {
                    char came[100];
                    deleteTextFiles(main_copy_of_exe_path_of_code);
                    sprintf(came, "copy %s %s", copy_s, main_copy_of_exe_path_of_code);
                    system(came);
                }
            }
            else
            {
                printf("you cant checkout because you have unstaged files.");
            }
        }

        else if (strncmp("bizhbi checkout -id", input, 17) == 0 && strcmp("bizhbi checkout HEAD", input) != 0)
        {
            char id[100];
            saparetor(input, id);
            char copy_un[100];
            strcpy(copy_un, currentDirectory);
            strcat(copy_un, "\\unstage");
            struct stat st;
            if (access(copy_un, F_OK) == -1 || st.st_size == 0)
            {

                char copy_s[100];
                strcpy(copy_s, currentDirectory);
                strcat(copy_s, "\\commit\\");
                strcat(copy_s, id);
                if (access(copy_s, F_OK) == -1)
                    printf("we dont have such a directory.");
                else
                {
                    char came[100];
                    deleteTextFiles(main_copy_of_exe_path_of_code);
                    sprintf(came, "copy %s %s", copy_s, main_copy_of_exe_path_of_code);
                    system(came);
                }
            }
            else
            {
                printf("you cant checkout because you have unstaged files.");
            }
        }

        else if (strcmp("bizhbi checkout HEAD", input) == 0)
        {
            char line[100];
            FILE *f = fopen(copy_head, "r");
            while (fgets(line, sizeof(line), f) != NULL)
            {
                printf("%s", line);
            }
        }

        // fashe 2
        // wm = without message
        else if (strncmp(input, "bizhbi revert whm", 17) == 0)
        {
            char id[100];
            saparetor(input, id);
            char copy_un[100];
            strcpy(copy_un, currentDirectory);
            strcat(copy_un, "\\unstage");
            struct stat st;
            if (access(copy_un, F_OK) == -1 || st.st_size == 0)
            {

                char copy_s[100];
                strcpy(copy_s, currentDirectory);
                strcat(copy_s, "\\commit\\");
                strcat(copy_s, id);
                if (access(copy_s, F_OK) == -1)
                {
                    printf("we dont have such a directory.");
                }
                else
                {
                    char came[100];
                    deleteTextFiles(main_copy_of_exe_path_of_code);
                    sprintf(came, "copy %s %s", copy_s, main_copy_of_exe_path_of_code);
                    system(came);
                }
            }
            else
            {
                printf("you cant reverse because you have unstaged files.");
            }
            if (access(directoryPath, F_OK) != -1)
            {

                FILE *ms = fopen(messsage, "r");
                char linems[100];
                int q = 1;
                int chq = 0;
                char *mess;
                char *des1;
                while (fgets(linems, sizeof(linems), ms) != NULL)
                {
                    linems[strcspn(linems, "\n")] = '\0';
                    if (q % 7 == 3)
                    {
                        mess = strtok(linems, ":");
                        mess = strtok(NULL, " ");
                        if (strcmp(mess, id) == 0)
                        {
                            chq = q + 1;
                        }
                    }
                    if (chq == q)
                    {
                        removeSpaces(linems);
                        des1 = strtok(linems, ":");
                        des1 = strtok(NULL, " ");
                        printf("%s", des1);
                        break;
                    }
                    q++;
                }
                fclose(ms);
                char line[300];
                // Get the current time
                time_t currentTime = time(NULL);
                char *timeString;
                int count = 0; // number of files that goes to staging.

                char line1[100];
                char *ptr;
                global_config_file = fopen(global, "r");
                if (global_config_file != NULL)
                {
                    while (fgets(line1, sizeof(line1), global_config_file) != NULL)
                    {
                        if (strstr(line1, "last") != NULL)
                        {
                            char *token;
                            token = strtok(line1, ":");
                            token = strtok(NULL, " ");
                            commit_id = atoi(token);
                            commit_id++;
                            ptr = malloc(sizeof(char) * 2);
                            sprintf(ptr, "%d", commit_id);
                        }
                    }
                }
                fclose(global_config_file);
                global_config_file = fopen(global, "r");
                char line2[100];
                FILE *fcommit = fopen(temp_c, "w");
                while (fgets(line2, sizeof(line2), global_config_file) != NULL)
                {
                    int len = strlen(line2);
                    line2[len] = '\0';

                    if (strstr(line2, "last") != NULL)
                    {
                        fprintf(fcommit, "last_commit_id : %s\n", ptr);
                    }
                    else
                    {
                        fprintf(fcommit, "%s", line2);
                    }
                }
                fclose(fcommit);
                fclose(global_config_file);
                remove(global);
                rename(temp_c, global);
                fclose(fcommit);
                char line3[100];
                FILE *gc = fopen(global, "r");
                char line_gc[100];
                char *saver_user;
                while (fgets(line_gc, sizeof(line_gc), gc) != NULL)
                {
                    saver_user = strtok(line_gc, ":");
                    saver_user = strtok(NULL, " ");
                    break;
                }
                fclose(gc);
                char mab[100];
                strcpy(mab, currentDirectory);
                strcat(mab, "\\commit\\");
                strcat(mab, id);
                // printf("++ %s\n",mab);
                DIR *dir;
                struct dirent *entry;

                // Open the directory
                dir = opendir(mab);
                if (dir == NULL)
                {
                    printf("Unable to open the directory.\n");
                    continue;
                }
                char copy_dir[100][100];
                int indexs = 0;
                while ((entry = readdir(dir)) != NULL)
                {
                    // Ignore the "." and ".." entries
                    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                    {
                        strcpy(copy_dir[indexs], entry->d_name);
                        // printf("%s\n",names_of_files[counter]);
                        indexs++;
                    }
                }

                // Close the directory
                closedir(dir);
                FILE *me = fopen(messsage, "a");
                for (int i = 0; i < indexs; i++)
                {
                    fprintf(me, "file : %s\n", copy_dir[i]);
                    fprintf(me, "username : %s\n", saver_user);
                    fprintf(me, "commit id : %d\n ", commit_id);
                    fprintf(me, "message is : %s\n", des1);
                    fprintf(me, "number of files in this commit is : %d\n", indexs);
                    timeString = ctime(&currentTime);
                    fprintf(me, "time : %s", timeString);
                    fprintf(me, "branch : %s\n", "master");
                }
                fclose(me);
                char commit_iid[100];
                char str[100];
                sprintf(str, "%d", commit_id);
                strcpy(commit_iid, currentDirectory);
                strcat(commit_iid, "\\commit\\");
                strcat(commit_iid, str);
                mkdir(commit_iid);
                char dastor[100];
                sprintf(dastor, "copy %s %s", mab, commit_iid);
                system(dastor);
            }

            else
            {
                FILE *ms = fopen(messsage, "r");
                char linems[100];
                int q = 1;
                int chq = 0;
                char *mess;
                char *des1;
                while (fgets(linems, sizeof(linems), ms) != NULL)
                {
                    linems[strcspn(linems, "\n")] = '\0';
                    if (q % 7 == 3)
                    {
                        mess = strtok(linems, ":");
                        mess = strtok(NULL, " ");
                        if (strcmp(mess, id) == 0)
                        {
                            chq = q + 1;
                        }
                    }
                    if (chq == q)
                    {
                        removeSpaces(linems);
                        des1 = strtok(linems, ":");
                        des1 = strtok(NULL, " ");
                        break;
                    }
                    q++;
                }
                fclose(ms);
                char commit_message[100];
                char line[300];
                FILE *message = fopen(messsage, "a");
                // Get the current time
                time_t currentTime = time(NULL);
                char *timeString;
                char line_user[100];
                char *ptr;
                char line_con[100];
                FILE *config = fopen(copy_config, "r");
                FILE *user = fopen(copy_info_saver, "r");
                char *token2;
                rewind(user);
                rewind(config);
                while (fgets(line_user, sizeof(line_user), user) != NULL)
                {
                    line_user[strcspn(line_user, "\n")] = '\0';
                    if (strstr(line_user, "Username") != NULL)
                    {
                        token2 = strtok(line_user, ":");
                        token2 = strtok(NULL, " ");
                        break;
                    }
                }
                int count_l = 1;
                rewind(config);
                int saver = 0;
                rewind(config);
                while (fgets(line_con, sizeof(line_con), config) != NULL)
                {
                    line_con[strlen(line_con) - 1] = '\0';
                    if ((count_l % 5 == 1))
                    {
                        char *extract;
                        extract = strtok(line_con, ":");
                        extract = strtok(NULL, " ");
                        if (strcmp(extract, token2) == 0)
                        {
                            saver = count_l + 2;
                        }
                    }
                    if (count_l == saver)
                    {
                        char *token;
                        token = strtok(line_con, ":");
                        token = strtok(NULL, " ");
                        commit_id = atoi(token);
                        commit_id++;
                        ptr = malloc(sizeof(char) * 2);
                        sprintf(ptr, "%d", commit_id);
                        break;
                    }
                    count_l++;
                }
                fclose(config);
                fclose(user);
                config = fopen(copy_config, "r");
                char line2[100];
                FILE *fcommit = fopen(temp_c, "w");
                int counter_c = 0;
                while (fgets(line2, sizeof(line2), config) != NULL)
                {
                    counter_c++;
                    if (counter_c == saver)
                    {
                        fprintf(fcommit, "last_commit_id : %s\n", ptr);
                    }
                    else
                    {
                        fprintf(fcommit, "%s", line2);
                    }
                }
                fclose(fcommit);
                fclose(config);
                remove(copy_config);
                rename(temp_c, copy_config);
                fclose(fcommit);
                //
                char line3[100];
                char mab[100];
                strcpy(mab, currentDirectory);
                strcat(mab, "\\commit\\");
                strcat(mab, id);
                // printf("++ %s\n",mab);
                DIR *dir;
                struct dirent *entry;

                // Open the directory
                dir = opendir(mab);
                if (dir == NULL)
                {
                    printf("Unable to open the directory.\n");
                    continue;
                }
                char copy_dir[100][100];
                int indexs = 0;
                while ((entry = readdir(dir)) != NULL)
                {
                    // Ignore the "." and ".." entries
                    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                    {
                        strcpy(copy_dir[indexs], entry->d_name);
                        // printf("%s\n",names_of_files[counter]);
                        indexs++;
                    }
                }

                // Close the directory
                closedir(dir);
                FILE *me = fopen(messsage, "a");
                for (int i = 0; i < indexs; i++)
                {
                    fprintf(me, "file : %s\n", copy_dir[i]);
                    fprintf(me, "username : %s\n", token2);
                    fprintf(me, "commit id : %d\n ", commit_id);
                    fprintf(me, "message is : %s\n", des1);
                    fprintf(me, "number of files in this commit is : %d\n", indexs);
                    timeString = ctime(&currentTime);
                    fprintf(me, "time : %s", timeString);
                    fprintf(me, "branch : %s\n", "master");
                }
                fclose(me);
                char commit_iid[100];
                char str[100];
                sprintf(str, "%d", commit_id);
                strcpy(commit_iid, currentDirectory);
                strcat(commit_iid, "\\commit\\");
                strcat(commit_iid, str);
                mkdir(commit_iid);
                char dastor[100];
                sprintf(dastor, "copy %s %s", mab, commit_iid);
                system(dastor);
            }
        }

        else if (strncmp(input, "bizhbi revert m", 15) == 0)
        {
            char *op[1000];
            int count = 0;
            char id[100];
            tokenizeStrings(input, op, &count);
            char messagee[100];
            strcpy(messagee, op[0]);
            strcpy(id, op[1]);
            // bizhbi revert <hello hi> "1"
            char copy_un[100];
            strcpy(copy_un, currentDirectory);
            strcat(copy_un, "\\unstage");
            struct stat st;
            if (access(copy_un, F_OK) == -1 || st.st_size == 0)
            {

                char copy_s[100];
                strcpy(copy_s, currentDirectory);
                strcat(copy_s, "\\commit\\");
                strcat(copy_s, id);
                if (access(copy_s, F_OK) == -1)
                    printf("we dont have such a directory.");
                else
                {
                    char came[100];
                    deleteTextFiles(main_copy_of_exe_path_of_code);
                    sprintf(came, "copy %s %s", copy_s, main_copy_of_exe_path_of_code);
                    system(came);
                }
            }
            else
            {
                printf("you cant reverse because you have unstaged files.");
            }

            if (access(directoryPath, F_OK) != -1)
            {

                FILE *ms = fopen(messsage, "r");
                fclose(ms);
                // Get the current time
                time_t currentTime = time(NULL);
                char *timeString;
                // number of files that goes to staging.

                char line1[100];
                char *ptr;
                global_config_file = fopen(global, "r");
                if (global_config_file != NULL)
                {
                    while (fgets(line1, sizeof(line1), global_config_file) != NULL)
                    {
                        if (strstr(line1, "last") != NULL)
                        {
                            char *token;
                            token = strtok(line1, ":");
                            token = strtok(NULL, " ");
                            commit_id = atoi(token);
                            commit_id++;
                            ptr = malloc(sizeof(char) * 2);
                            sprintf(ptr, "%d", commit_id);
                        }
                    }
                }
                fclose(global_config_file);
                global_config_file = fopen(global, "r");
                char line2[100];
                FILE *fcommit = fopen(temp_c, "w");
                while (fgets(line2, sizeof(line2), global_config_file) != NULL)
                {
                    int len = strlen(line2);
                    line2[len] = '\0';

                    if (strstr(line2, "last") != NULL)
                    {
                        fprintf(fcommit, "last_commit_id : %s\n", ptr);
                    }
                    else
                    {
                        fprintf(fcommit, "%s", line2);
                    }
                }
                fclose(fcommit);
                fclose(global_config_file);
                remove(global);
                rename(temp_c, global);
                fclose(fcommit);
                char line3[100];
                FILE *gc = fopen(global, "r");
                char line_gc[100];
                char *saver_user;
                while (fgets(line_gc, sizeof(line_gc), gc) != NULL)
                {
                    saver_user = strtok(line_gc, ":");
                    saver_user = strtok(NULL, " ");
                    break;
                }
                fclose(gc);
                char mab[100];
                strcpy(mab, currentDirectory);
                strcat(mab, "\\commit\\");
                strcat(mab, id);
                // printf("++ %s\n",mab);
                DIR *dir;
                struct dirent *entry;

                // Open the directory
                dir = opendir(mab);
                if (dir == NULL)
                {
                    printf("Unable to open the directory.\n");
                    continue;
                }
                char copy_dir[100][100];
                int indexs = 0;
                while ((entry = readdir(dir)) != NULL)
                {
                    // Ignore the "." and ".." entries
                    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                    {
                        strcpy(copy_dir[indexs], entry->d_name);
                        // printf("%s\n",names_of_files[counter]);
                        indexs++;
                    }
                }

                // Close the directory
                closedir(dir);
                FILE *me = fopen(messsage, "a");
                for (int i = 0; i < indexs; i++)
                {
                    fprintf(me, "file : %s\n", copy_dir[i]);
                    fprintf(me, "username : %s\n", saver_user);
                    fprintf(me, "commit id : %d\n ", commit_id);
                    fprintf(me, "message is : %s\n", messagee);
                    fprintf(me, "number of files in this commit is : %d\n", indexs);
                    timeString = ctime(&currentTime);
                    fprintf(me, "time : %s", timeString);
                    fprintf(me, "branch : %s\n", "master");
                }
                fclose(me);
                char commit_iid[100];
                char str[100];
                sprintf(str, "%d", commit_id);
                strcpy(commit_iid, currentDirectory);
                strcat(commit_iid, "\\commit\\");
                strcat(commit_iid, str);
                mkdir(commit_iid);
                char dastor[100];
                sprintf(dastor, "copy %s %s", mab, commit_iid);
                system(dastor);
            }

            else
            {
                FILE *ms = fopen(messsage, "r");
                char linems[100];
                int q = 1;
                int chq = 0;
                char *mess;
                char *des1;
                while (fgets(linems, sizeof(linems), ms) != NULL)
                {
                    linems[strcspn(linems, "\n")] = '\0';
                    if (q % 7 == 3)
                    {
                        mess = strtok(linems, ":");
                        mess = strtok(NULL, " ");
                        if (strcmp(mess, id) == 0)
                        {
                            chq = q + 1;
                        }
                    }
                    if (chq == q)
                    {
                        des1 = strtok(linems, ":");
                        des1 = strtok(NULL, " ");
                        break;
                    }
                    q++;
                }
                fclose(ms);
                char commit_message[100];
                char line[300];
                FILE *message = fopen(messsage, "a");
                // Get the current time
                time_t currentTime = time(NULL);
                char *timeString;
                char line_user[100];
                char *ptr;
                char line_con[100];
                FILE *config = fopen(copy_config, "r");
                FILE *user = fopen(copy_info_saver, "r");
                char *token2;
                rewind(user);
                rewind(config);
                while (fgets(line_user, sizeof(line_user), user) != NULL)
                {
                    line_user[strcspn(line_user, "\n")] = '\0';
                    if (strstr(line_user, "Username") != NULL)
                    {
                        token2 = strtok(line_user, ":");
                        token2 = strtok(NULL, " ");
                        break;
                    }
                }
                int count_l = 1;
                rewind(config);
                int saver = 0;
                rewind(config);
                while (fgets(line_con, sizeof(line_con), config) != NULL)
                {
                    line_con[strlen(line_con) - 1] = '\0';
                    if ((count_l % 5 == 1))
                    {
                        char *extract;
                        extract = strtok(line_con, ":");
                        extract = strtok(NULL, " ");
                        if (strcmp(extract, token2) == 0)
                        {
                            saver = count_l + 2;
                        }
                    }
                    if (count_l == saver)
                    {
                        char *token;
                        token = strtok(line_con, ":");
                        token = strtok(NULL, " ");
                        commit_id = atoi(token);
                        commit_id++;
                        ptr = malloc(sizeof(char) * 2);
                        sprintf(ptr, "%d", commit_id);
                        break;
                    }
                    count_l++;
                }
                fclose(config);
                fclose(user);
                config = fopen(copy_config, "r");
                char line2[100];
                FILE *fcommit = fopen(temp_c, "w");
                int counter_c = 0;
                while (fgets(line2, sizeof(line2), config) != NULL)
                {
                    counter_c++;
                    if (counter_c == saver)
                    {
                        fprintf(fcommit, "last_commit_id : %s\n", ptr);
                    }
                    else
                    {
                        fprintf(fcommit, "%s", line2);
                    }
                }
                fclose(fcommit);
                fclose(config);
                remove(copy_config);
                rename(temp_c, copy_config);
                fclose(fcommit);
                //
                char line3[100];
                char mab[100];
                strcpy(mab, currentDirectory);
                strcat(mab, "\\commit\\");
                strcat(mab, id);
                // printf("++ %s\n",mab);
                DIR *dir;
                struct dirent *entry;

                // Open the directory
                dir = opendir(mab);
                if (dir == NULL)
                {
                    printf("Unable to open the directory.\n");
                    continue;
                }
                char copy_dir[100][100];
                int indexs = 0;
                while ((entry = readdir(dir)) != NULL)
                {
                    // Ignore the "." and ".." entries
                    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                    {
                        strcpy(copy_dir[indexs], entry->d_name);
                        // printf("%s\n",names_of_files[counter]);
                        indexs++;
                    }
                }

                // Close the directory
                closedir(dir);
                FILE *me = fopen(messsage, "a");
                for (int i = 0; i < indexs; i++)
                {
                    fprintf(me, "file : %s\n", copy_dir[i]);
                    fprintf(me, "username : %s\n", token2);
                    fprintf(me, "commit id : %d\n ", commit_id);
                    fprintf(me, "message is : %s\n", messagee);
                    fprintf(me, "number of files in this commit is : %d\n", indexs);
                    timeString = ctime(&currentTime);
                    fprintf(me, "time : %s", timeString);
                    fprintf(me, "branch : %s\n", "master");
                }
                fclose(me);
                char commit_iid[100];
                char str[100];
                sprintf(str, "%d", commit_id);
                strcpy(commit_iid, currentDirectory);
                strcat(commit_iid, "\\commit\\");
                strcat(commit_iid, str);
                mkdir(commit_iid);
                char dastor[100];
                sprintf(dastor, "copy %s %s", mab, commit_iid);
                system(dastor);
            }
        }

        else if (strncmp(input, "bizhbi revert -n", 16) == 0)
        {
            char id[100];
            if (strstr(input, "\"") != NULL)
            {
                saparetor(input, id);
                char copy_un[100];
                strcpy(copy_un, currentDirectory);
                strcat(copy_un, "\\unstage");
                struct stat st;
                if (access(copy_un, F_OK) == -1 || st.st_size == 0)
                {

                    char copy_s[100];
                    strcpy(copy_s, currentDirectory);
                    strcat(copy_s, "\\commit\\");
                    strcat(copy_s, id);
                    if (access(copy_s, F_OK) == -1)
                        printf("we dont have such a directory.");
                    else
                    {
                        char came[100];
                        deleteTextFiles(main_copy_of_exe_path_of_code);
                        sprintf(came, "copy %s %s", copy_s, main_copy_of_exe_path_of_code);
                        system(came);
                    }
                }
                else
                {
                    printf("you cant do this action because you have unstaged files.");
                }
            }

            else
            {
                char copy_c[100];
                strcpy(copy_c, currentDirectory);
                strcat(copy_c, "\\commit");
                char copy_com[100];
                strcpy(copy_com, copy_c);
                strcat(copy_com, "\\*");
                struct dirent *entry;
                struct stat fileStat;
                WIN32_FIND_DATA findFileData;
                HANDLE hFind = FindFirstFile(_T(copy_com), &findFileData);

                if (hFind == INVALID_HANDLE_VALUE)
                {
                    _tprintf(_T("Error opening directory\n"));
                    continue;
                }

                FILETIME latestTime = findFileData.ftCreationTime;
                TCHAR latestFolder[MAX_PATH];
                _tcscpy(latestFolder, findFileData.cFileName);

                while (FindNextFile(hFind, &findFileData) != 0)
                {
                    if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    {
                        if (CompareFileTime(&findFileData.ftCreationTime, &latestTime) > 0)
                        {
                            latestTime = findFileData.ftCreationTime;
                            _tcscpy(latestFolder, findFileData.cFileName);
                        }
                    }
                }

                FindClose(hFind);
                _tprintf(_T("Latest folder: %s\n"), latestFolder);
                strcat(copy_c, "\\");
                strcat(copy_c, latestFolder);
                char dost[100];
                deleteTextFiles(main_copy_of_exe_path_of_code);
                sprintf(dost, "copy %s %s", copy_c, main_copy_of_exe_path_of_code);
                system(dost);
            }
        }

        else if (strcmp(input, "bizhbi pre-commit") == 0)
        {

            char hook[100];
            DIR *dir;
            struct dirent *entry;
            struct stat fileStat;

            // Open the directory
            dir = opendir(copy_fstaging);
            if (dir == NULL)
            {
                printf("Unable to open the directory.\n");
            }

            // Read each entry in the directory
            while ((entry = readdir(dir)) != NULL)
            {
                // Get the file status
                stat(entry->d_name, &fileStat);
                // Check if the entry is a regular file and not a hidden file
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                {
                    char copy_s[100];
                    strcpy(copy_s, copy_fstaging);
                    strcat(copy_s, "\\\\");
                    strcat(copy_s, entry->d_name);
                    // printf("%s\n", entry->d_name);

                    // codes for calling functions.
                    char copy_hook[100];
                    strcpy(copy_hook, currentDirectory);
                    strcat(copy_hook, "\\\\hook.txt");
                    FILE *hello = fopen(copy_hook, "r");
                    char lines[100];
                    while (fgets(lines, sizeof(lines), hello) != NULL)
                    {
                        // printf("HI");
                        lines[strcspn(lines, "\n")] = '\0';
                        if (strcmp(lines, "character-limit") == 0)
                        {
                            characters(copy_s);
                        }
                        if (strcmp(lines, "time-limit") == 0)
                        {
                            checkFileTimes(copy_s);
                        }
                        if (strcmp(lines, "file-size-check") == 0)
                        {
                            isFileLarge(copy_s);
                        }
                        if (strcmp(lines, "format-check") == 0)
                        {
                            isFormatCorrect(entry->d_name);
                        }
                        if (strcmp(lines, "todo-check") == 0)
                        {
                            TODO(copy_s);
                        }
                        if (strcmp(lines, "eof-blank-space") == 0)
                        {
                            whitespace(copy_s);
                        }
                    }
                    // checkFileTimes(copy_s);
                    // isFileLarge(copy_s);
                    // isFormatCorrect(entry->d_name);
                    // characters(copy_s);
                    // whitespace(copy_s);
                    // TODO(copy_s);
                }
            }

            // Close the directory
            closedir(dir);
        }

        else if (strncmp(input, "bizhbi pre-commit add hook", 26) == 0)
        {
            char hook[100];
            saparetor(input, hook);
            char copy_hook[100];
            strcpy(copy_hook, currentDirectory);
            strcat(copy_hook, "\\\\hook.txt");
            FILE *h = fopen(copy_hook, "a");
            fprintf(h, "%s\n", hook);
            fclose(h);
        }

        else if (strncmp(input, "bizhbi pre-commit applied hooks", 31) == 0)
        {

            char copy_hook[100];
            strcpy(copy_hook, currentDirectory);
            strcat(copy_hook, "\\\\hook.txt");
            FILE *h = fopen(copy_hook, "r");
            char line[100];
            while (fgets(line, sizeof(line), h) != NULL)
            {
                printf("%s", line);
            }
            fclose(h);
        }

        else if (strncmp(input, "bizhbi pre-commit remove hook", 29) == 0)
        {
            char hook[100];
            FILE *f = fopen(temp_c, "w");
            char copy_hook[100];
            strcpy(copy_hook, currentDirectory);
            strcat(copy_hook, "\\\\hook.txt");
            FILE *h = fopen(copy_hook, "r");
            saparetor(input, hook);
            char line[100];
            while (fgets(line, sizeof(line), h) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, hook) != 0)
                {
                    fprintf(f, "%s\n", line);
                }
            }
            fclose(f);
            fclose(h);
            remove(copy_hook);
            rename(temp_c, copy_hook);
            fclose(f);
        }

        else if (strncmp("bizhbi pre-commit -f", input, 20) == 0)
        { // error staging nemide
            char *res[1000];
            char a[100][100];
            int flag_error_for_not_exist = 0;
            int can = token_del(res, input);
            for (int d = 0; d < can; d++)
            {
                if (fileExists(res[d]))
                {
                    char copy_hook[100];
                    char *base = basename(res[d]);
                    strcpy(copy_hook, currentDirectory);
                    strcat(copy_hook, "\\\\hook.txt");
                    FILE *hello = fopen(copy_hook, "r");
                    char lines[100];
                    printf("%s\n", base);
                    while (fgets(lines, sizeof(lines), hello) != NULL)
                    {
                        lines[strcspn(lines, "\n")] = '\0';
                        if (strcmp(lines, "character-limit") == 0)
                        {
                            characters(res[d]);
                        }
                        if (strcmp(lines, "time-limit") == 0)
                        {
                            checkFileTimes(res[d]);
                        }
                        if (strcmp(lines, "file-size-check") == 0)
                        {
                            isFileLarge(res[d]);
                        }
                        if (strcmp(lines, "format-check") == 0)
                        {
                            isFormatCorrect(base);
                        }
                        if (strcmp(lines, "todo-check") == 0)
                        {
                            TODO(res[d]);
                        }
                        if (strcmp(lines, "eof-blank-space") == 0)
                        {
                            whitespace(res[d]);
                        }
                    }
                }
                else
                {
                    printf("The path does not exist\n");
                    flag_error_for_not_exist = 1;
                }
            }
        }

        else if (strncmp(input, "bizhbi pre-commit hooks list", 28) == 0)
        {
            printf("%s\n", "todo-check");
            printf("%s\n", "eof-blank-space");
            printf("%s\n", "format-check");
            printf("%s\n", "balance-braces");
            printf("%s\n", "indentation-check");
            printf("%s\n", "static-error-check");
            printf("%s\n", "file-size-check");
            printf("%s\n", "character-limit");
            printf("%s\n", "time-limit");
        }

        else if (strncmp(input, "bizhbi grep -f", 14) == 0) // bizhbi grep -f <E:\Git_proj\bizhbi\unstage\hi.txt><hi>
        {
            char *add_res[100];
            int save[1000];
            char b[100][100];
            int base = 0;
            int ll = 1;
            int ondex = 0;
            token_del(add_res, input);
            FILE *k = fopen(add_res[0], "r");
            char line[100];
            while (fgets((line), 100, k) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';

                char *extract[1000];
                int index = 0;
                char delimeter[] = " ";
                char *ptr = strtok(line, delimeter);
                while (ptr != NULL)
                {
                    extract[index] = ptr;
                    if (strcmp(extract[index], add_res[1]) == 0)
                    {
                        strcpy(b[base], line);
                        base++;
                        save[ondex] = ll;
                        ondex++;
                        break;
                    }
                    index++;
                    ptr = strtok(NULL, delimeter);
                }
                ll++;
            }
            fclose(k);
            for (int lk = 0; lk < ondex; lk++)
            {
                printf("%d\n", save[lk]);
            }
            for (int h = 0; h < base; h++)
            {
                printf("%s\n", b[h]);
                printf("\033[0;34m");
                printf("%s\n", add_res[1]);
            }
        }

        else if (strncmp(input, "bizhbi grep -c", 14) == 0) // bizhbi grep -c <filename><commit_id><word>
        {
            char b[100][100];
            int base = 0;
            char *add_res[100];
            int save[1000];
            int ll = 1;
            int ondex = 0;
            token_del(add_res, input);
            // printf("%s\n", add_res[0]);
            // printf("%s\n", add_res[1]);
            // printf("%s\n", add_res[2]);
            char file_Add[100];
            strcpy(file_Add, currentDirectory);
            strcat(file_Add, "\\commit\\");
            strcat(file_Add, add_res[1]);
            strcat(file_Add, "\\\\");
            strcat(file_Add, add_res[0]);
            strcat(file_Add, ".txt");
            FILE *k = fopen(file_Add, "r");
            char line[100];
            while (fgets((line), 100, k) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                /* if (strstr(line, add_res[1]) != NULL)
                 {
                     save[ondex] = ll;
                     ondex++;
                 }*/

                char *extract[1000];
                int index = 0;
                char delimeter[] = " ";
                char *ptr = strtok(line, delimeter);
                while (ptr != NULL)
                {
                    extract[index] = ptr;
                    if (strcmp(extract[index], add_res[2]) == 0)
                    {
                        strcpy(b[base], line);
                        base++;
                        save[ondex] = ll;
                        ondex++;
                        break;
                    }
                    index++;
                    ptr = strtok(NULL, delimeter);
                }
                ll++;
            }
            fclose(k);
            for (int lk = 0; lk < ondex; lk++)
            {
                printf("%d\n", save[lk]);
            }
            for (int h = 0; h < base; h++)
            {
                printf("%s\n", b[h]);
                printf("\033[0;34m");
                printf("%s\n", add_res[2]);
            }
        }
    }
}
