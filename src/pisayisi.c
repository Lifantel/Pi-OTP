//Pİ saysını kulllanarak 6 basamaklı şifre oluşturan kod.
//Hiçbir sorumluluk üstlenmiyorum.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <curl/curl.h>

#include "kbhit.h"


struct MemoryStruct {
    char  *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        printf("Yetersiz hafıza!\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void get_pi_digits_from_api(long long start_index, char *output_code) {
    CURL *curl_handle;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size   = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    if (curl_handle) {
        char url[256];
        sprintf(url, "https://api.pi.delivery/v1/pi?start=%lld&numberOfDigits=6", start_index);

        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        res = curl_easy_perform(curl_handle);

        if (res == CURLE_OK) {
            char *content_start = strstr(chunk.memory, "\"content\":\"");
            if (content_start) {
                strncpy(output_code, content_start + 11, 6);
                output_code[6] = '\0';
            } else {
                strcpy(output_code, "ERROR1");
            }
        } else {
            strcpy(output_code, "ERROR2");
        }

        curl_easy_cleanup(curl_handle);
        free(chunk.memory);
    }

    curl_global_cleanup();
}

int main(void) {
    char otp[7] = {0};

    printf("Pi-OTP Doğrulayıcı Başlatıldı...\n");
    printf("Çıkmak için 'q' tuşuna basın.\n\n");

    kbhit_init();

    while (1) {
        long long current_time = (long long)time(NULL);
        int       kalan_sure   = 20 - (int)(current_time % 20);
        long long time_step    = current_time / 20;
        long long start_index  = (time_step * 1234567891LL) % 1000000000LL;

        if (current_time % 20 == 0 || otp[0] == '\0') {
            printf("\n[API] Yeni şifre verisi çekiliyor...\n");
            get_pi_digits_from_api(start_index, otp);
        }

        printf("\rGüncel Şifre: %s | Kalan Süre: %02d saniye  ", otp, kalan_sure);
        fflush(stdout);

        int tus = kbhit_getch();
        if (tus == 'q' || tus == 'Q') {
            printf("\n\nCıkılıyor...\n");
            break;
        }

        sleep(1);
    }

    kbhit_cleanup(); 
    return 0;
}
