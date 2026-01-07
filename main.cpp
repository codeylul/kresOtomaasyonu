#include <iostream>
#include <string>
#include <math.h> //matematiksel işlemleri kullanmak için
#include <time.h>
#include <string> //string sınıfını kullanmak için
#include <limits> //sayı limitlerini (min max kullanmak için)
#include <fstream>//girdi çıktıları yapabildiğimiz kütüphane
#include <filesystem>

using namespace std;

// Ogrenci bilgilerini tutan yapi
struct Ogrenci {
    int id;
    char ad[30];
    char soyad[30];
    int yas;
};

class KresSistemi {
private:
    string dosyaAdi;

public:
    KresSistemi() {
        dosyaAdi = "kres_verileri.dat";
    }

    // 1. OGRENCI EKLEME
    void ekle() {
        Ogrenci yeniOgr;
        cout << "Ogrenci ID: "; cin >> yeniOgr.id;
        cout << "Ad: "; cin >> yeniOgr.ad;
        cout << "Soyad: "; cin >> yeniOgr.soyad;
        cout << "Yas: "; cin >> yeniOgr.yas;

        ofstream dosya(dosyaAdi, ios::binary | ios::app);
        dosya.write((char*)&yeniOgr, sizeof(Ogrenci));
        dosya.close();
        cout << "Kayit basariyla eklendi.\n";
    }

    // 2. LISTELEME
    void listele() {
        Ogrenci ogr;
        ifstream dosya(dosyaAdi, ios::binary);

        if (!dosya) {
            cout << "Dosya bulunamadi veya kayit yok!\n";
            return;
        }

        cout << "\n--- KRES OGRENCI LISTESI ---\n";
        while (dosya.read((char*)&ogr, sizeof(Ogrenci))) {
            cout << "ID: " << ogr.id << " | Isim: " << ogr.ad << " " << ogr.soyad
                 << " | Yas: " << ogr.yas << endl;
        }
        dosya.close();
    }

    // 3. ARAMA (ID'ye gore)
    void ara() {
        int arananId;
        bool bulundu = false;
        Ogrenci ogr;
        cout << "Aranacak Ogrenci ID girin: "; cin >> arananId;

        ifstream dosya(dosyaAdi, ios::binary);
        while (dosya.read((char*)&ogr, sizeof(Ogrenci))) {
            if (ogr.id == arananId) {
                cout << "Kayit Bulundu: " << ogr.ad << " " << ogr.soyad << " (Yas: " << ogr.yas << ")\n";
                bulundu = true;
                break;
            }
        }
        dosya.close();
        if (!bulundu) cout << "Kayit bulunamadi.\n";
    }

    // 4. SILME (Gecici dosya kullanarak)
    void sil() {
        int silinecekId;
        bool bulundu = false;
        Ogrenci ogr;
        cout << "Silinecek Ogrenci ID girin: "; cin >> silinecekId;

        ifstream dosya(dosyaAdi, ios::binary);
        ofstream gecici("gecici.dat", ios::binary);

        while (dosya.read((char*)&ogr, sizeof(Ogrenci))) {
            if (ogr.id != silinecekId) {
                gecici.write((char*)&ogr, sizeof(Ogrenci));
            } else {
                bulundu = true;
            }
        }

        dosya.close();
        gecici.close();

        remove(dosyaAdi.c_str());             // Eski dosyayi sil
        rename("gecici.dat", dosyaAdi.c_str()); // Yeni dosyayi asil dosya yap

        if (bulundu) cout << "Kayit silindi.\n";
        else cout << "Silinecek kayit bulunamadi.\n";
    }
};

int main() {
    KresSistemi kres;
    int secim;

    do {
        cout << "\n--- OZEL KRES OTOMASYONU ---\n";
        cout << "1- Ogrenci Ekle\n";
        cout << "2- Listele\n";
        cout << "3- Ogrenci Ara\n";
        cout << "4- Ogrenci Sil\n";
        cout << "0- Cikis\n";
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
            case 1: kres.ekle(); break;
            case 2: kres.listele(); break;
            case 3: kres.ara(); break;
            case 4: kres.sil(); break;
        }
    } while (secim != 0);

    return 0;
}
