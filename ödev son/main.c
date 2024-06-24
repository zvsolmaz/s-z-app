// GRUP 27
// 434364 SENA KOÇASLAN
// 425443 ZEYNEP VUSLAT SOLMAZ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ORDERS 100

#ifndef CONFIG_H
#define CONFIG_H

// Dosya yolları
#define yemek_listesi_txt "C:\\Users\\zeynep\\OneDrive\\Desktop\\yemek listesi (1).txt"
#define siparisler_txt "C:\\Users\\zeynep\\OneDrive\\Desktop\\siparis.txt"

#endif // CONFIG_H

void menuGoster();

/////////////////////////////////////////////////////      Musterı Uygulamasi Fonksiyonlari     ////////////////////////////////////////////////////////////////

void musteri();
void menuGoster1();
void yeniSiparis();
int sonKullaniciAdiniOku();
void sonKullaniciAdiniYaz(int sonKullaniciAdi);
void mevcutSiparisDurumu();
void oncekiSiparislerim();

typedef struct {
    char kullaniciAdi[50];
    int sifre;
} Kullanici;

//////////////////////////////////////////////////////    Restoran Uygulamasi Fonksiyonlari     /////////////////////////////////////////////////////////////////

void restoran();
void menuGoster2();
void yemekEkleGuncelleSil();
void yemekEkle();
void yemekGuncelle();
void yemekSil();
void siparisOnayRed();
void gunlukRaporAlGoster();
void gunlukRaporAl();
void gunlukRaporGoster();
void analizler();
void gunlukKazanc();
void aylikKazanc();
void donemKazanci();
void enCokTuketim();
void asci();
void asciSayisiAl();
int AsciSayisiKullan();
void AsciSayisiDegistir(int yeniSayisi);
int asciSayisi=-1;

////////////////////////////////////////////////////      Mutfak Uygulamasi Fonksiyonlari      //////////////////////////////////////////////////////////////////

char siparisler[MAX_ORDERS][512];
int siparisSayaci = 0;
int asciSayaci;
time_t asciBitisZamani[MAX_ORDERS]; //time() işlevi kullanılabilir. Bu işlev, sistem saatine göre geçen saniye sayısını döndürür ve bu değer bir time_t türünden değişkenin içine atanabilir.

void mutfak();
void siparisOku();
void siparisDurumKontrol();
void asciBitisZamaniBaslat();
void asciBitisZamaniYazdir() ;
void asciAta();
void siparisYazdir();


int main()
{
    int secim;
    printf("Hosgeldiniz!\n");
    do{

    menuGoster();
    printf("\nKullanmak istediginiz uygulamayi secin:\n");
    scanf("%d",&secim);
    switch(secim){
        case 1:
            musteri();
            break;
        case 2:
            restoran();
            break;
        case 3:
            mutfak();
            break;
        case 0:
            printf("Cikis yapiliyor...\n");
            break;
        default:
            printf("Gecersiz secim!\n");
            break;
    }
        }while(secim != 0);

    return 0;
}

// Menüyü göster
void menuGoster() {
    printf("\n--- ReYeTap S & Z ---\n");
    printf("1. Musteri Girisi\n");
    printf("2. Restorant Girisi\n");
    printf("3. Mutfak Girisi\n");
    printf("0. Cikis\n");
}



//////////////////////////////////////////////////////////////     Musteri Uygulamasi     //////////////////////////////////////////////////////////////////////



void musteri() {
    int secim;
    do {
        menuGoster1();
        printf("Bir secim yapiniz: ");
        scanf("%d", &secim);
        switch (secim) {
            case 1:
                yeniSiparis();
                break;
            case 2:
                mevcutSiparisDurumu();
                break;
            case 3:
                oncekiSiparislerim();
                break;
            case 0:
                printf("Ust Menuye Donuluyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
                break;
        }
    } while (secim != 0);
}

void menuGoster1() {
    printf("\n--- Musteri Menu ---\n");
    printf("1. Yeni Siparis\n");
    printf("2. Mevcut Siparis Durumu\n");
    printf("3. Onceki Siparislerim\n");
    printf("0. Cikis\n");
}

void yeniSiparis() {
    Kullanici kullanici;
    printf("Kullanici Adi: ");
    scanf("%s", kullanici.kullaniciAdi);
    printf("Sifre: ");
    scanf("%d", &kullanici.sifre);

    FILE *dosya = fopen(yemek_listesi_txt, "r");
    if (dosya == NULL) {
        printf("Dosya açılamadı.\n");
        return;
    }

    FILE *siparisDosyasi = fopen(siparisler_txt, "a");
    if (siparisDosyasi == NULL) {
        printf("Sipariş dosyası açılamadı.\n");
        fclose(dosya);
        return;
    }

    printf("Menu:\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Menu NO\t   Yemek Adi\t\tYemek Fiyati\t\tHazirlanma Suresi\t\tMevcudiyet\n");
    printf("---------------------------------------------------------------------------------------------------\n");

    char satir[100];
    while (fgets(satir, sizeof(satir), dosya)) {  //fgets dosyadan satır satır okuma yapar
        char mevcudiyet[50];
        sscanf(satir, "%*d %*s %*f %*s %*f %s", mevcudiyet); //sscanf fonksiyonu, bir karakter dizisinden biçimlendirilmiş verileri okumak için kullanılır,satırı parçalar
        if (strcmp(mevcudiyet, "Mevcut") == 0) { //  strcmp parametreleri eşitse 0a eşitliyor
            printf("%s", satir);
        }
    }
    printf("\n-------------------------------------------------------------------------------------------------\n");

    char cevap;
    float toplamFatura = 0.0;
    int kullaniciSayisi = sonKullaniciAdiniOku();
    if (kullaniciSayisi == 0) {
        kullaniciSayisi = 1;
    }

    do {
        printf("Siparis vermek istiyor musunuz? (y/n): ");
        scanf(" %c", &cevap);

        if (cevap == 'y') {
            int secilenMenuNo;
            printf("Lutfen bir menu numarasi girin: ");
            scanf("%d", &secilenMenuNo);

            fseek(dosya, 0, SEEK_SET); //imleci dosyanın başına getiriyor
            float fiyat, hazirlanmaDakika;
            char yemekAdi[50];
            char paraBirimi[10];
            char mevcudiyet[50];

            while (fgets(satir, sizeof(satir), dosya)) {
                int menuNo;
                sscanf(satir, "%d %s %f %s %f %s", &menuNo, yemekAdi, &fiyat, paraBirimi, &hazirlanmaDakika, mevcudiyet);
                if (menuNo == secilenMenuNo && strcmp(mevcudiyet, "Mevcut") == 0) {
                    printf("Secilen Yemek: %s\n", yemekAdi);
                    printf("Fiyat: %.2f %s\n", fiyat, paraBirimi);
                    printf("Hazirlanma : %.2f dk\n", hazirlanmaDakika);
                    printf("Mevcudiyet: %s\n", mevcudiyet);

                    // Dosyaya yazdır
                    time_t t = time(NULL);
                    struct tm tm = *localtime(&t);
                    fprintf(siparisDosyasi, "\nSIP%d%d%d.%.3d ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, kullaniciSayisi);
                    //Ocak ayı 0 olarak temsil edilir ve yıl 1900'den başlar. Bu nedenle, ayı ve yılı doğru bir şekilde elde etmek için ay değerine 1 ve yıl değerine 1900 eklenmelidir.
                    fprintf(siparisDosyasi, "%s", yemekAdi);
                    fprintf(siparisDosyasi, " %.2f %s", fiyat, paraBirimi);
                    fprintf(siparisDosyasi, " Hazirlanma : %.2f dk", hazirlanmaDakika);
                    fprintf(siparisDosyasi, " User:%s-%d", kullanici.kullaniciAdi, kullanici.sifre);
                    fprintf(siparisDosyasi, " Durum:Beklemede\n "); // Durumu yaz
                    toplamFatura += fiyat;
                    break;
                }
            }
        } else if (cevap != 'n') {
            printf("Gecersiz bir cevap girdiniz.\n");
        }

        if (cevap == 'n') {
            kullaniciSayisi++;
            sonKullaniciAdiniYaz(kullaniciSayisi);
        }

    } while (cevap != 'n');

    printf("\nToplam Fatura: %.2f TL\n", toplamFatura);

    fclose(dosya);
    fclose(siparisDosyasi);
}

// Son kullanılan kullanıcı adını dosyaya yazar
void sonKullaniciAdiniYaz(int sonKullaniciAdi) {
    FILE *dosya = fopen("son_kullanici.txt", "w");
    if (dosya == NULL) {
        printf("Son kullanici dosyasi olusturulamadi.\n");
        return;
    }
    fprintf(dosya, "%d", sonKullaniciAdi);
    fclose(dosya);
}

// Dosyadan son kullanılan kullanıcı adını okur
int sonKullaniciAdiniOku() {
    FILE *dosya = fopen("son_kullanici.txt", "r");
    if (dosya == NULL) {
        return 0; // Dosya yoksa veya okunamazsa varsayılan olarak 0 döndür
    }
    int sonKullaniciAdi;
    fscanf(dosya, "%d", &sonKullaniciAdi);
    fclose(dosya);
    return sonKullaniciAdi;
}



void mevcutSiparisDurumu() {
    Kullanici kullanici;
    printf("Kullanici Adi: ");
    scanf("%s", kullanici.kullaniciAdi);
    printf("Sifre: ");
    scanf("%d", &kullanici.sifre);

    FILE *siparisDosyasi = fopen(siparisler_txt, "r");
    if (siparisDosyasi == NULL) {
        printf("Sipariş dosyası açılamadı.\n");
        return;
    }

    char satir[200];
    printf("Mevcut Siparisleriniz:\n");
    int bulundu = 0; // Kullanıcının siparişinin bulunduğunu kontrol etmek için
    while (fgets(satir, sizeof(satir), siparisDosyasi)) {
        char sifreStr[20];
        sprintf(sifreStr, "%d", kullanici.sifre); // Şifreyi string dizisine dönüştür
        if (strstr(satir, kullanici.kullaniciAdi) != NULL && strstr(satir, sifreStr) != NULL) {
            if (strstr(satir, "Durum:Beklemede") != NULL || strstr(satir, "Durum:Hazirlaniyor") != NULL) {
                printf("%s", satir);
                bulundu = 1;
            }
        }
    }
    if (!bulundu) {
        printf("Hatali kullanici adi veya sifre!\n");
    }

    fclose(siparisDosyasi);
}

void oncekiSiparislerim() {
    Kullanici kullanici;
    printf("Kullanici Adi: ");
    scanf("%s", kullanici.kullaniciAdi);
    printf("Sifre: ");
    scanf("%d", &kullanici.sifre);

    FILE *siparisDosyasi = fopen(siparisler_txt, "r");
    if (siparisDosyasi == NULL) {
        printf("Sipariş dosyası açılamadı.\n");
        return;
    }

    char satir[200];
    printf("Onceki Siparisleriniz:\n");
    int bulundu = 0; // Kullanıcının siparişinin bulunduğunu kontrol etmek için
    while (fgets(satir, sizeof(satir), siparisDosyasi)) {
        char sifreStr[20];
        sprintf(sifreStr, "%d", kullanici.sifre); // Şifreyi karakter dizisine dönüştür
        if (strstr(satir, kullanici.kullaniciAdi) != NULL && strstr(satir, sifreStr) != NULL) {
            if (strstr(satir, "Durum:Teslim Edildi") != NULL || strstr(satir, "Durum:Gecersiz") != NULL) {
                printf("%s", satir);
                bulundu = 1;
            }
        }
    }
    if (!bulundu) {
        printf("Hatali kullanici adi veya sifre!\n");
    }

    fclose(siparisDosyasi);
}





//////////////////////////////////////////////////////////////     Restoran Uygulamasi     /////////////////////////////////////////////////////////////////////





void restoran() {
    int secim1;
    do {
        menuGoster2();
        printf("Bir secim yapiniz: ");
        scanf("%d", &secim1);
        switch(secim1) {
            case 1:
                yemekEkleGuncelleSil();
                break;
            case 2:
                siparisOnayRed();
                break;
            case 3:
                gunlukRaporAlGoster();
                break;
            case 4:
                analizler();
                break;
            case 5:
                asci();
                break;
            case 0:
                printf("Ust Menuye Donuluyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
                break;
        }
    } while(secim1 != 0);
    return 0;
}

void menuGoster2() {
    printf("\n--- Restoran Menu ---\n");
    printf("1. Yemek Ekle-Yemek Guncelle-Yemek Sil\n");
    printf("2. Yeni Siparis Onay/Red\n");
    printf("3. Gunluk Rapor Alma-Rapor Goruntuleme \n");
    printf("4. Analizler\n");
    printf("5. Asci Sayisi Belirleme\n");
    printf("0. Cikis\n");
}

void yemekEkleGuncelleSil() {
    int secim2;
    printf("1. Yemek Ekle\n");
    printf("2. Yemek Guncelle\n");
    printf("3. Yemek Sil\n");
    printf("Seciminizi yapin: ");
    scanf("%d", &secim2);

    switch (secim2) {
        case 1:
            yemekEkle();
            break;
        case 2:
            yemekGuncelle();
            break;
        case 3:
            yemekSil();
            break;
        default:
            printf("Gecersiz secim!\n");
            break;
    }
}

void yemekEkle() {
    FILE *file = fopen(yemek_listesi_txt, "a+");
    if (file == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    printf("Menu:\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Menu NO\t   Yemek Adi\t\tYemek Fiyati\t\tHazirlanma Suresi\t\tMevcudiyet\n");
    printf("---------------------------------------------------------------------------------------------------\n");

    char satir[100];
    while (fgets(satir, sizeof(satir), file)) {
        printf("%s", satir);
    }

    printf("\n-------------------------------------------------------------------------------------------------\n");

    // Dosyaya eklemek için yeni yemek bilgilerini al
    int sure, maxMenuNo = 0, currentMenuNo;
    char isim[50], fiyat[20], durum[20];
    char tempIsim[50], tempFiyat[20], tempDurum[20];
    char buffer[200];
    // Buffer, dosyadan okunan her bir satırın geçici olarak depolanması için kullanılan bir karakter dizisidir
    // Dosyadaki en yüksek menü numarasını bul
    rewind(file);// imleci dosyanın başın alır

    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d %s %s %d %s", &currentMenuNo, tempIsim, tempFiyat, &sure, tempDurum);
        if (currentMenuNo > maxMenuNo) {
            maxMenuNo = currentMenuNo;
        }
    }

    int newMenuNo = maxMenuNo + 1;

    // Yeni yemek bilgilerini al
    printf("Yemek Ismi: ");
    scanf("%s", isim);
    printf("Fiyat: ");
    scanf("%s", fiyat);
    strcat(fiyat, " TL"); // strcat fiyatın yanına "TL" ekle,iki karakter dizisini birleştirmek için kullanılır.
    printf("Hazirlanma Suresi(dk): ");
    scanf("%d", &sure);
    printf("Durum (Mevcut/Mevcut_Degil): ");
    scanf("%s", durum);

    // Yeni yemeği dosyaya yaz
    fprintf(file, "%-4d         %-20s   %-16s              %-16d      %s\n", newMenuNo, isim, fiyat, sure, durum);

    fclose(file);
    printf("Yemek eklendi.\n");
}

void yemekGuncelle() {
    FILE *file = fopen(yemek_listesi_txt, "r+");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    printf("Menu:\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Menu NO\t   Yemek Adi\t\tYemek Fiyati\t\tHazirlanma Suresi\t\tMevcudiyet\n");
    printf("---------------------------------------------------------------------------------------------------\n");

    char satir[100];
    while (fgets(satir, sizeof(satir), file)) {

            printf("%s", satir);

    }
    printf("\n-------------------------------------------------------------------------------------------------\n");

    // Guncellemek istenen yemeğin adını al
    char updateIsim[50];
    printf("Guncellemek istediginiz yemek ismi: ");
    scanf("%s", updateIsim);

    int found = 0;
    rewind(file);
    char buffer[200];
    while (fgets(buffer, sizeof(buffer), file)) {
        int menuNo,sure;
        char isim[50], fiyat[20], durum[20];
        sscanf(buffer, "%d %s %s %d %s", &menuNo, isim, fiyat, &sure, durum);
        if (strcmp(isim, updateIsim) == 0) {
            found = 1;
            printf("Yeni Yemek Ismi: ");
            scanf("%s", isim);
            printf("Yeni Fiyat: ");
            scanf("%s", fiyat);
            strcat(fiyat, " TL");
            printf("Yeni Hazirlanma Suresi(dk): ");
            scanf("%d", &sure);
            printf("Yeni Durum (Mevcut/Mevcut_Degil): ");
            scanf("%s", durum);
            fprintf(tempFile, "%-4d         %-20s   %-16s              %-16d      %s\n", menuNo, isim, fiyat, sure, durum);
        } else {
            fprintf(tempFile, "%s", buffer);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(yemek_listesi_txt);
    rename("temp.txt", yemek_listesi_txt);

    if (found) {
        printf("Yemek guncellendi.\n");
    } else {
        printf("Yemek ismi bulunamadi.\n");
    }
}

void yemekSil() {
    FILE *file = fopen(yemek_listesi_txt, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    printf("Menu:\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Menu NO\t   Yemek Adi\t\tYemek Fiyati\t\tHazirlanma Suresi\t\tMevcudiyet\n");
    printf("---------------------------------------------------------------------------------------------------\n");

    char satir[100];
    while (fgets(satir, sizeof(satir), file)) {

            printf("%s", satir);
        }

    printf("\n-------------------------------------------------------------------------------------------------\n");

    // Silinecek yemeğin adını al
    char deleteIsim[50];
    printf("Silmek istediginiz yemek ismi: ");
    scanf("%s", deleteIsim);

    int found = 0;
    rewind(file);
    char buffer[200];
    while (fgets(buffer, sizeof(buffer), file)) {
        char isim[50], fiyat[20], durum[20];
        sscanf(buffer, "%*d %s %*s %*d %s", isim, durum);
        if (strcmp(isim, deleteIsim) == 0) {
            found = 1;
        } else {
            fprintf(tempFile, "%s", buffer);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(yemek_listesi_txt);
    rename("temp.txt", yemek_listesi_txt);

    if (found) {
        printf("Yemek silindi.\n");
    } else {
        printf("Yemek ismi bulunamadi.\n");
    }
}


void siparisOnayRed() {
    char siparisID[20];
    int secim;
    printf("Islem yapmak istediginiz siparisin ID'sini girin: ");
    scanf("%s", siparisID);

    FILE *siparisDosyasi = fopen(siparisler_txt, "r+");
    if (siparisDosyasi == NULL) {
        printf("Siparis dosyasi acilamadi.\n");
        return;
    }

    FILE *tempDosya = fopen("temp.txt", "w");
    if (tempDosya == NULL) {
        printf("Gecici dosya olusturulamadi.\n");
        fclose(siparisDosyasi);
        return;
    }

    char satir[200];
    int bulundu = 0;
    while (fgets(satir, sizeof(satir), siparisDosyasi)) {
        if (strstr(satir, siparisID) != NULL) {
            bulundu = 1;
            printf("Siparisi onaylamak icin 1'e, reddetmek icin 2'ye basin: ");
            scanf("%d", &secim);

            // Durum kısmını bul
            char *durumBaslangic = strstr(satir, "Durum:");
            if (durumBaslangic != NULL) {
                // Satırın başından Durum kısmına kadar olan kısmı kopyala
                fprintf(tempDosya, "%.*s", (int)(durumBaslangic - satir), satir);
                // Durumu seçime göre değiştir
                if (secim == 1) {
                    fprintf(tempDosya, "Durum:Hazirlaniyor\n");
                    printf("Siparis onaylandi.\n");
                } else if (secim == 2) {
                    fprintf(tempDosya, "Durum:Gecersiz\n");
                    printf("Siparis reddedildi.\n");
                } else {
                    printf("Gecersiz secim!\n");
                }
            }
        } else {
            fputs(satir, tempDosya); //fputs karakteri dosyaya yazar
        }
    }

    fclose(siparisDosyasi);
    fclose(tempDosya);

    remove(siparisler_txt);
    rename("temp.txt", siparisler_txt);

    if (!bulundu) {
        printf("Siparis ID bulunamadi.\n");
    }
}


void gunlukRaporAlGoster() {
    int secim3;
    printf("1. Gunluk Rapor Al\n");
    printf("2. Gunluk  Rapor Goster\n");
    printf("Seciminizi yapin: ");
    scanf("%d", &secim3);

    switch (secim3) {
        case 1:
            gunlukRaporAl();
            break;
        case 2:
            gunlukRaporGoster();
            break;
        default:
            printf("Gecersiz secim!\n");
            break;
    }
}

void gunlukRaporAl() {
    //otomatik alınması için windows görev zamanlayıcı kullanılabilir ya da verimsiz olan sleep(86400)fonksiyonu kullanılabilir.
    FILE *siparisDosyasi = fopen(siparisler_txt, "r");
    if (siparisDosyasi == NULL) {
        printf("Siparis dosyasi acilamadi.\n");
        return;
    }

    // Bugünün tarihini al
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char dosyaAdi[100];
    snprintf(dosyaAdi, sizeof(dosyaAdi), "siparisler_%d-%02d-%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    // snprintf in tasma hatalarini onleyen versiyonu
    FILE *gunlukRaporDosyasi = fopen(dosyaAdi, "w");
    if (gunlukRaporDosyasi == NULL) {
        printf("Gunluk rapor dosyasi olusturulamadi.\n");
        fclose(siparisDosyasi);
        return;
    }

    char satir[200];
    while (fgets(satir, sizeof(satir), siparisDosyasi)) {
        fputs(satir, gunlukRaporDosyasi);
    }

    fclose(siparisDosyasi);
    fclose(gunlukRaporDosyasi);

    // Eski siparisler.txt dosyasını temizle
    siparisDosyasi = fopen(siparisler_txt, "w");
    fclose(siparisDosyasi);

    printf("Gunluk rapor alindi ve '%s' dosyasina kaydedildi.\n", dosyaAdi);
}


void gunlukRaporGoster() {
    char tarih[20];
    printf("Goruntulemek istediginiz tarihinizi girin (YYYY-MM-DD): ");
    scanf("%s", tarih);

    char dosyaAdi[100];
    snprintf(dosyaAdi, sizeof(dosyaAdi), "siparisler_%s.txt", tarih);

    FILE *gunlukRaporDosyasi = fopen(dosyaAdi, "r");
    if (gunlukRaporDosyasi == NULL) {
        printf("Rapor dosyasi acilamadi.\n");
        return;
    }

    char satir[200];
    printf("\n--- %s Tarihli Siparisler ---\n", tarih);
    while (fgets(satir, sizeof(satir), gunlukRaporDosyasi)) {
        printf("%s", satir);
    }

    fclose(gunlukRaporDosyasi);
}

void analizler() {
    int secim4;
    printf("1. Gunluk Kazanc\n");
    printf("2. Aylik Kazanc\n");
    printf("3. Donem Kazanci\n");
    printf("4. En Cok Tuketim\n");
    printf("Seciminizi yapin: ");
    scanf("%d", &secim4);

    switch (secim4) {
        case 1:
            gunlukKazanc();
            break;
        case 2:
            aylikKazanc();
            break;
        case 3:
            donemKazanci();
            break;
        case 4:
            enCokTuketim();
            break;
        default:
            printf("Gecersiz secim!\n");
            break;
    }
}


void gunlukKazanc() {

    char tarih[20];
    printf("Goruntulemek istediginiz tarihi girin (YYYY-MM-DD): ");
    scanf("%s", tarih);

    char dosyaAdi[100];
    snprintf(dosyaAdi, sizeof(dosyaAdi), "siparisler_%s.txt", tarih);

    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    double gunlukToplamKazanc = 0.0;
    char satir[200];
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        // "Durum: Teslim Edildi" içeriyorsa fiyatı al
        if (strstr(satir, "Teslim Edildi") != NULL) {
            double fiyat;
            // Satırdan fiyat bilgisini TL ibaresinden önceki değer olarak oku
            if (sscanf(satir, "%*s %*s %lf TL", &fiyat) == 1) {
                // Günlük kazanca ekle
                gunlukToplamKazanc += fiyat;
            }
        }
    }

    fclose(dosya);

    printf("Gunluk Kazanc: %.2f TL\n", gunlukToplamKazanc);
}

void aylikKazanc() {
    // Ay ve yıl bilgisini al
    int ay, yil;
    printf("Ay bilgisini girin (1-12): ");
    scanf("%d", &ay);
    printf("Yil bilgisini girin: ");
    scanf("%d", &yil);

    // Toplam kazancı saklamak için değişken
    double toplamKazanc = 0.0;

    // Her günün raporunu oku ve kazancı topla
    for (int gun = 1; gun <= 31; gun++) {
        char dosyaAdi[100];
        snprintf(dosyaAdi, sizeof(dosyaAdi), "siparisler_%d-%02d-%02d.txt", yil, ay, gun);

        FILE *gunlukRaporDosyasi = fopen(dosyaAdi, "r");
        if (gunlukRaporDosyasi == NULL) {
            // Dosya yoksa diğer güne geç
            continue;
        }

        char satir[200];
        double fiyat;
        int teslimEdildiMi = 0;

        while (fgets(satir, sizeof(satir), gunlukRaporDosyasi) != NULL) {
            // Satırda "Durum: Teslim Edildi" varsa teslimEdildiMi bayrağını ayarla
            if (strstr(satir, "Durum:Teslim Edildi") != NULL) {
                teslimEdildiMi = 1;
            }

            // Satırda fiyat bilgisi varsa ve teslim edildi ise fiyatı al
            if (teslimEdildiMi && sscanf(satir, "%*s %*s %lf TL", &fiyat) == 1) {
                toplamKazanc += fiyat;
                teslimEdildiMi = 0; // Fiyatı topladıktan sonra bayrağı sıfırla
            }
        }

        fclose(gunlukRaporDosyasi);
    }

    printf("Toplam aylik kazanc: %.2f TL\n", toplamKazanc);
}
void donemKazanci() {

    int baslangicGun, baslangicAy, baslangicYil;
    int bitisGun, bitisAy, bitisYil;

    printf("Baslangic tarihini girin (gun ay yil): ");
    scanf("%d %d %d", &baslangicGun, &baslangicAy, &baslangicYil);
    printf("Bitis tarihini girin (gun ay yil): ");
    scanf("%d %d %d", &bitisGun, &bitisAy, &bitisYil);

    double toplamKazanc = 0.0;

    for (int yil = baslangicYil; yil <= bitisYil; yil++) {
        int baslangicAyi = (yil == baslangicYil) ? baslangicAy : 1;
        int bitisAyi = (yil == bitisYil) ? bitisAy : 12;

        for (int ay = baslangicAyi; ay <= bitisAyi; ay++) {
            int baslangicGunu = (yil == baslangicYil && ay == baslangicAy) ? baslangicGun : 1;
            int bitisGunu = (yil == bitisYil && ay == bitisAy) ? bitisGun : 31;

            for (int gun = baslangicGunu; gun <= bitisGunu; gun++) {
                char dosyaAdi[100];
                snprintf(dosyaAdi, sizeof(dosyaAdi), "siparisler_%d-%02d-%02d.txt", yil, ay, gun);

                FILE *dosya = fopen(dosyaAdi, "r");
                if (dosya == NULL) {
                    printf("Dosya acilamadi: %s\n", dosyaAdi);
                    continue; // Dosya yoksa diğer güne geç
                }

                char satir[200];
                while (fgets(satir, sizeof(satir), dosya) != NULL) {
                    // "Durum: Teslim Edildi" içeriyorsa fiyatı al
                    if (strstr(satir, "Teslim Edildi") != NULL) {
                        double fiyat;
                        // Satırdan fiyat bilgisini TL ibaresinden önceki değer olarak oku
                        if (sscanf(satir, "%*s %*s %lf TL", &fiyat) == 1) {
                            // Günlük kazanca ekle
                            toplamKazanc += fiyat;
                        }
                    }
                }

                fclose(dosya);
            }
        }
    }

    printf("Belirtilen donemdeki toplam kazanc: %.2f TL\n", toplamKazanc);
}

void enCokTuketim() {

typedef struct {
    char yemekAdi[50];
    int siparisSayisi;
} Yemek;

typedef struct {
    char kullaniciAdi[50];
    int siparisSayisi;
} Kullanici;

typedef struct {
    char gunAdi[50];
    double toplamKazanc;
} Gun;


    int baslangicGun, baslangicAy, baslangicYil;
    int bitisGun, bitisAy, bitisYil;

    printf("Baslangic tarihini girin (gun ay yil): ");
    scanf("%d %d %d", &baslangicGun, &baslangicAy, &baslangicYil);
    printf("Bitis tarihini girin (gun ay yil): ");
    scanf("%d %d %d", &bitisGun, &bitisAy, &bitisYil);

    // En çok sipariş edilen yemeği ve miktarını saklamak için değişkenler
    Yemek enCokSiparisEdilenYemek = {"", 0};

    // En kazançlı günü ve miktarını saklamak için değişkenler
    Gun enKazancliGun = {"", 0.0};

    // En çok sipariş veren kullanıcıyı ve sipariş sayısını saklamak için değişkenler
    Kullanici enCokSiparisVerenKullanici = {"", 0};

    // Toplam yemek hazırlama süresini saklamak için değişken
    int toplamHazirlamaSuresi = 0;

    // Toplam kazancı saklamak için değişken
    double toplamKazanc = 0.0;

    // Sipariş sayısını takip etmek için kullanıcı adı ve sayısını saklayan dinamik dizi
    Kullanici kullaniciListesi[1000];
    int kullaniciSayisi = 0;

    // Yemek siparişlerini takip etmek için dinamik dizi
    Yemek yemekListesi[1000];
    int yemekSayisi = 0;

    // Günlük kazançları takip etmek için dinamik dizi
    Gun gunListesi[1000];
    int gunSayisiList = 0;

    // Tarih aralığında dosyaları oku ve analizleri yap
    for (int yil = baslangicYil; yil <= bitisYil; yil++) {
        int baslangicAyi = (yil == baslangicYil) ? baslangicAy : 1;
        int bitisAyi = (yil == bitisYil) ? bitisAy : 12;

        for (int ay = baslangicAyi; ay <= bitisAyi; ay++) {
            int baslangicGunu = (yil == baslangicYil && ay == baslangicAy) ? baslangicGun : 1;
            int bitisGunu = (yil == bitisYil && ay == bitisAy) ? bitisGun : 31;

            for (int gun = baslangicGunu; gun <= bitisGunu; gun++) {
                char dosyaAdi[100];
                snprintf(dosyaAdi, sizeof(dosyaAdi), "siparisler_%d-%02d-%02d.txt", yil, ay, gun);

                FILE *dosya = fopen(dosyaAdi, "r");
                if (dosya == NULL) {
                    printf("Dosya acilamadi: %s\n", dosyaAdi);
                    continue;
                }

                char satir[200];
                double gunlukKazanc = 0.0;
                while (fgets(satir, sizeof(satir), dosya) != NULL) {
                    // Yemek adını, fiyatı ve kullanıcıyı satırdan al
                    char yemekAdi[50], userID[50];
                    double fiyat;
                    if (sscanf(satir, "SIP%*s %49s %lf TL %*s %*s %*s %*s User:%49s %*s", yemekAdi, &fiyat, userID) == 3) {
                        // Yemek sipariş sayısını güncelle
                        int yemekBulundu = 0;
                        for (int i = 0; i < yemekSayisi; i++) {
                            if (strcmp(yemekListesi[i].yemekAdi, yemekAdi) == 0) {
                                yemekListesi[i].siparisSayisi++;
                                yemekBulundu = 1;
                                break;
                            }
                        }
                        if (!yemekBulundu) {
                            strcpy(yemekListesi[yemekSayisi].yemekAdi, yemekAdi);
                            yemekListesi[yemekSayisi].siparisSayisi = 1;
                            yemekSayisi++;
                        }

                        // Toplam kazancı güncelle
                        toplamKazanc += fiyat;
                        gunlukKazanc += fiyat;

                        // Kullanıcı sipariş sayısını güncelle
                        int kullaniciBulundu = 0;
                        for (int i = 0; i < kullaniciSayisi; i++) {
                            if (strcmp(kullaniciListesi[i].kullaniciAdi, userID) == 0) {
                                kullaniciListesi[i].siparisSayisi++;
                                kullaniciBulundu = 1;
                                break;
                            }
                        }
                        if (!kullaniciBulundu) {
                            strcpy(kullaniciListesi[kullaniciSayisi].kullaniciAdi, userID);
                            kullaniciListesi[kullaniciSayisi].siparisSayisi = 1;
                            kullaniciSayisi++;
                        }
                    }

                    // Hazırlama süresini satırdan al
                    int baslangicSaat, baslangicDakika, bitisSaat, bitisDakika;
                    if (sscanf(satir, "%*s %*s %*s %*s Baslangic: %*d.%*d.%*d-%d.%d Bitis: %*d.%*d.%*d-%d.%d %*s %*s %*s", &baslangicSaat, &baslangicDakika, &bitisSaat, &bitisDakika) == 4) {
                        int hazirlamaSuresi = (bitisSaat * 60 + bitisDakika) - (baslangicSaat * 60 + baslangicDakika);
                        toplamHazirlamaSuresi += hazirlamaSuresi;
                    }
                }

                fclose(dosya);

                // Günlük kazancı güncelle
                int gunBulundu = 0;
                for (int i = 0; i < gunSayisiList; i++) {
                    if (strcmp(gunListesi[i].gunAdi, dosyaAdi) == 0) {
                        gunListesi[i].toplamKazanc += gunlukKazanc;
                        gunBulundu = 1;
                        break;
                    }
                }
                if (!gunBulundu) {
                    strcpy(gunListesi[gunSayisiList].gunAdi, dosyaAdi);
                    gunListesi[gunSayisiList].toplamKazanc = gunlukKazanc;
                    gunSayisiList++;
                }
            }
        }
    }

    // En çok sipariş edilen yemeği bul
    for (int i = 0; i < yemekSayisi; i++) {
        if (yemekListesi[i].siparisSayisi > enCokSiparisEdilenYemek.siparisSayisi) {
            enCokSiparisEdilenYemek = yemekListesi[i];
        }
    }

    // En çok sipariş veren kullanıcıyı bul
    for (int i = 0; i < kullaniciSayisi; i++) {
        if (kullaniciListesi[i].siparisSayisi > enCokSiparisVerenKullanici.siparisSayisi) {
            enCokSiparisVerenKullanici = kullaniciListesi[i];
        }
    }

    // En kazançlı günü bul
    for (int i = 0; i < gunSayisiList; i++) {
        if (gunListesi[i].toplamKazanc > enKazancliGun.toplamKazanc) {
            enKazancliGun = gunListesi[i];
        }
    }


     // Analiz sonuçlarını kullanıcıya göster
    printf("En Cok Siparis Edilen Yemek: %s (Siparis Sayisi:%d)\n", enCokSiparisEdilenYemek.yemekAdi, enCokSiparisEdilenYemek.siparisSayisi);
    printf("En Kazancli Gun: %s (Kazanc: %.2f TL)\n", enKazancliGun.gunAdi, enKazancliGun.toplamKazanc);
    printf("En Cok Siparis Veren Kullanici: %s (Siparis Sayisi: %d)\n", enCokSiparisVerenKullanici.kullaniciAdi, enCokSiparisVerenKullanici.siparisSayisi);
    printf("Toplam Hazirlama Suresi: %d dakika\n", toplamHazirlamaSuresi);
    printf("Toplam Kazanc: %.2f TL\n", toplamKazanc);
}
// Aşçı sayısı alt menüsünü gösterme fonksiyonu
void asci() {
    int altSecim;
    do {
        printf("\nAsci Sayisi Menusu:\n");
        printf("1. Asci Sayisini Al\n");
        printf("2. Asci Sayisini Degistir\n");
        printf("0. Geri Don\n");
        printf("Bir secim yapiniz: ");
        scanf("%d", &altSecim);
        switch (altSecim) {
            case 1:
                printf("Mevcut asci sayisi: %d\n", AsciSayisiKullan());
                break;
            case 2:
                printf("Yeni asci sayisini giriniz: ");
                int yeniSayisi;
                scanf("%d", &yeniSayisi);
                AsciSayisiDegistir(yeniSayisi);
                break;
            case 0:
                printf("Geri donuluyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
                break;
        }
    } while (altSecim != 0);
}
void asciSayisiAl() {
    if (asciSayisi == -1) { // Aşçı sayısı daha önce alınmadıysa
        printf("Restoraninizin calisan asci sayisini giriniz:\n");
        scanf("%d", &asciSayisi);
        printf("Calisan asci sayiniz %d olarak girilmistir.\n", asciSayisi);
    }
}

int AsciSayisiKullan() {
    if (asciSayisi == -1) { // Aşçı sayısı daha önce alınmadıysa
        asciSayisiAl(); // Aşçı sayısını al
    }
    return asciSayisi;
}

// Aşçı sayısını değiştiren fonksiyon
void AsciSayisiDegistir(int yeniSayisi) {
    asciSayisi = yeniSayisi;
    printf("Yeni calisan asci sayisi %d olarak ayarlandi.\n", asciSayisi);
}





//////////////////////////////////////////////////////////////     Mutfak Uygulamasi     //////////////////////////////////////////////////////////////////////





void siparisOku() {
    FILE *file = fopen(siparisler_txt, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(siparisler[siparisSayaci], sizeof(siparisler[siparisSayaci]), file)) {
        siparisler[siparisSayaci][strcspn(siparisler[siparisSayaci], "\n")] = '\0';
        // strcspn satır sonundaki yeni satır karakteri (\n) kaldırılmış olur
        siparisSayaci++;
    }

    fclose(file);
}

void siparisDurumKontrol() {
    time_t current_time;
    time(&current_time);

    for (int i = 0; i < siparisSayaci; i++) {
        char *status = strstr(siparisler[i], "Durum:");
        if (status == NULL) {
            continue;
        }

        char *end_time_str = strstr(siparisler[i], "Bitis Zamani:");
        if (end_time_str == NULL) {
            continue;
        }

        // Bitiş zamanını oku ve karşılaştır
        struct tm end_tm;
        end_time_str += strlen("Bitis Zamani:");
        int year, month, day, hour, min, sec;
        sscanf(end_time_str, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &min, &sec);
        end_tm.tm_year = year - 1900;
        end_tm.tm_mon = month - 1;
        end_tm.tm_mday = day;
        end_tm.tm_hour = hour;
        end_tm.tm_min = min;
        end_tm.tm_sec = sec;
        end_tm.tm_isdst = -1; // Daylight saving time correction
        time_t end_time = mktime(&end_tm);

        if (end_time < current_time && strstr(status, "Hazirlaniyor")) {
            // Eğer bitiş zamanı şimdiki zamandan küçükse ve durum "Hazırlanıyor" ise, durumu "Teslim Edildi" olarak değiştir.
            strncpy(status + strlen("Durum:"), "Teslim Edildi ", strlen("Teslim Edildi "));
            //status + strlen("Durum:"): "Durum:" ifadesinin sonundan başlayarak, status dizisinin bu konumunu işaret eder. Yani, "Durum:" ifadesinden sonraki ilk karakterin konumunu gösterir.
        }
    }
}

void asciBitisZamaniBaslat() {
    int asciSayaci = AsciSayisiKullan();
    FILE *file = fopen("chef_end_times.txt", "r");
    if (file != NULL) {
        int i = 0;
        while (i < asciSayaci && fscanf(file, "%ld", &asciBitisZamani[i]) == 1) {
            i++;
        }
        fclose(file);
        time_t simdiki_zaman;
        time(&simdiki_zaman);
        for (; i < asciSayaci; i++) {
            asciBitisZamani[i] = simdiki_zaman;
        }
    } else {
        time_t simdiki_zaman;
        time(&simdiki_zaman);
        for (int i = 0; i < asciSayaci; i++) {
            asciBitisZamani[i] = simdiki_zaman;
        }
    }
}


void asciBitisZamaniYazdir() {
    int asciSayaci = AsciSayisiKullan();
    FILE *file = fopen("chef_end_times.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < asciSayaci; i++) {
        fprintf(file, "%ld\n", asciBitisZamani[i]);
    }

    fclose(file);
}

void asciAta() {
    int asciSayaci = AsciSayisiKullan();
    for (int i = 0; i < siparisSayaci; i++) {
        char *durum = strstr(siparisler[i], "Durum:");
        char *asci = strstr(siparisler[i], "Asci:");

        if (durum == NULL || strstr(durum, "Hazirlaniyor") == NULL || asci != NULL) {
            continue;
        }

        int asciIndex = 0;
        time_t min_bitis_zamani = asciBitisZamani[0];
        for (int j = 1; j < asciSayaci; j++) {
            if (asciBitisZamani[j] < min_bitis_zamani) {
                asciIndex = j;
                min_bitis_zamani = asciBitisZamani[j];
            }
        }

        time_t simdiki_zaman = min_bitis_zamani;
        struct tm *start_tm = localtime(&simdiki_zaman);
        char baslangic_zamani[20];
        strftime(baslangic_zamani, sizeof(baslangic_zamani), "%Y-%m-%d %H:%M:%S", start_tm);
        // strftime fonksiyonu, bu zaman yapısındaki bileşenlerden (yıl, ay, gün, saat, dakika, saniye) yararlanarak biçim dizesinde belirtilen tarih ve saat formatına göre karakter dizisini oluşturur.

        int hazirlanma_zamani;
        sscanf(strstr(siparisler[i], "Hazirlanma :") + strlen("Hazirlanma :"), "%d", &hazirlanma_zamani);
        time_t bitis_zamani = simdiki_zaman + hazirlanma_zamani * 60;
        asciBitisZamani[asciIndex] = bitis_zamani;

        struct tm *end_tm = localtime(&bitis_zamani);
        char end_time_str[20];
        strftime(end_time_str, sizeof(end_time_str), "%Y-%m-%d %H:%M:%S", end_tm);

        char chef_str[6];
        sprintf(chef_str, "A%d", asciIndex + 1);

        char new_order[512];
        sprintf(new_order, "%s Asci:%s Baslangic Zamani:%s Bitis Zamani:%s",
                siparisler[i], chef_str, baslangic_zamani, end_time_str);

        strcpy(siparisler[i], new_order);
    }

    asciBitisZamaniYazdir();
}

void siparisYazdir() {
    printf("Siparisler:\n");
    for (int i = 0; i < siparisSayaci; i++) {
        printf("%s\n", siparisler[i]);
    }
}

void mutfak() {
    siparisOku();
    siparisDurumKontrol();

    asciBitisZamaniBaslat();
    asciAta();

    FILE *file = fopen(siparisler_txt, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < siparisSayaci; i++) {
        fprintf(file, "%s\n", siparisler[i]);
    }

    fclose(file);

    siparisYazdir();
}
