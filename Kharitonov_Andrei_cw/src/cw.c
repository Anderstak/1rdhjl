#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SENTENCE_LENGTH 1024  // Максимальная длина строки

// Объявление функций
void print_help();
char **read_text(size_t *size);
void free_text(char **text, size_t size);
char **split_into_sentences(char *text, size_t *size);
void replace_vowels(char **text, size_t size);
void find_longer_substrings(char **text, size_t size);
void remove_sentences_with_word_length(char **text, size_t *size, size_t length);
void sort_by_last_char(char **text, size_t size);
int compare_last_char(const void *a, const void *b);  // Объявление функции сравнения
void print_text(char **text, size_t size);

int main() {
    printf("Course work for option 4.10, by Andrei Kharitonov.\n");

    printf("Enter a command (0-5):\n");
    int command;
    if (scanf("%d", &command) != 1 || command < 0 || command > 5) {
        printf("Error: Invalid command. Please enter a number between 0 and 5.\n");
        return 1;  // Выход из программы, если введена неправильная команда
    }
    getchar();  // Ожидаем нажатия Enter после ввода команды

    if (command == 5) {
        print_help();  // Вывод справки по командам
        return 0;
    }

    if (command == 0) {
        printf("Exiting the program.\n");  // Выход из программы
        return 0;
    }

    size_t size = 0;
    char **text = read_text(&size);  // Чтение текста с клавиатуры
    if (!text) {
        printf("Error: Failed to read text.\n");
        return 1;
    }

    char *input_text = malloc(MAX_SENTENCE_LENGTH * size);  // Выделение памяти для всего текста
    input_text[0] = '\0';  // Инициализация строки

    // Собираем все строки текста в одну строку
    for (size_t i = 0; i < size; i++) {
        strcat(input_text, text[i]);
        strcat(input_text, " ");
    }

    char **sentences = split_into_sentences(input_text, &size);  // Разделяем текст на предложения

    // В зависимости от команды выполняем соответствующую операцию
    switch (command) {
        case 1:
            printf("Replacing all vowels with the next letter in the alphabet.\n");
            replace_vowels(sentences, size);  // Замена гласных
            print_text(sentences, size);  // Выводим результат
            break;

        

        default:
            printf("Error: Unknown command.\n");  // Если команда неизвестна
            break;
    }

    free_text(sentences, size);  // Освобождаем память, выделенную для предложений
    free(input_text);  // Освобождаем память для всей строки
    return 0;
}

// Функция для вывода справки по командам
void print_help() {
    printf("Help for available commands:\n");
    printf("1: Replace all vowels with the next letter in the alphabet.\n");
    printf("2: Find sentences of the form \"To <substring1> or not to <substring2>\" and print the longer substring.\n");
    printf("3: Remove all sentences where the first word has a length of 4.\n");
    printf("4: Sort sentences by the ASCII code of the last significant character.\n");
    printf("5: Display this help information.\n");
    printf("0: Exit the program.\n");
}

// Функция для чтения текста с клавиатуры
char **read_text(size_t *size) {
    char **text = NULL;
    char buffer[MAX_SENTENCE_LENGTH];
    *size = 0;

    printf("Enter text (press Enter twice to finish):\n");
    while (fgets(buffer, MAX_SENTENCE_LENGTH, stdin)) {
        if (strcmp(buffer, "\n") == 0) break;

        char *start = buffer;
        while (isspace((unsigned char)*start)) start++;
        char *end = start + strlen(start) - 1;
        while (end > start && isspace((unsigned char)*end)) *end-- = '\0';

        char **temp = realloc(text, (*size + 1) * sizeof(char *));
        if (!temp) {
            free_text(text, *size);  // Очистка памяти при ошибке
            return NULL;
        }
        text = temp;

        text[*size] = strdup(start);
        if (!text[*size]) {
            free_text(text, *size);
            return NULL;
        }
        (*size)++;
    }

    return text;
}

// Функция для освобождения памяти, выделенной для текста
void free_text(char **text, size_t size) {
    if (text) {
        for (size_t i = 0; i < size; i++) {
            free(text[i]);
        }
        free(text);
    }
}

// Функция для разделения текста на предложения
char **split_into_sentences(char *text, size_t *size) {
    size_t capacity = 10;
    *size = 0;
    char **sentences = malloc(capacity * sizeof(char *));
    if (!sentences) {
        return NULL;  // Если не удалось выделить память
    }

    char *sentence_start = text;
    char *p = text;

    // Проходим по тексту и разделяем его на предложения
    while (*p) {
        if (*p == '.' || *p == '!' || *p == '?') {  // Разделители предложений
            size_t length = p - sentence_start + 1;
            char *sentence = malloc(length + 1);
            if (!sentence) {
                free(sentences);
                return NULL;  // Если не удалось выделить память
            }

            strncpy(sentence, sentence_start, length);  // Копируем предложение
            sentence[length] = '\0';

            sentences[*size] = sentence;
            (*size)++;

            if (*size >= capacity) {
                capacity *= 2;  // Увеличиваем размер массива
                sentences = realloc(sentences, capacity * sizeof(char *));
                if (!sentences) {
                    return NULL;
                }
            }

            sentence_start = p + 1;  // Начинаем новое предложение
        }
        p++;
    }

    return sentences;
}

// Функция для замены гласных на следующую букву в алфавите
void replace_vowels(char **text, size_t size) {
    const char vowels[] = "aeiouyAEIOUY";
    for (size_t i = 0; i < size; i++) {
        for (char *p = text[i]; *p; p++) {
            char *vowel_pos = strchr(vowels, *p);  // Находим гласную
            if (vowel_pos) {
                // Заменяем на следующую букву
                if (*p == 'u') *p = 'v';
                else if (*p == 'U') *p = 'V';
                else if (*p == 'y') *p = 'z';
                else if (*p == 'Y') *p = 'Z';
                else *p = *p + 1;
            }
        }
    }
}



// Функция для вывода текста
void print_text(char **text, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%s\n", text[i]);
    }
}
