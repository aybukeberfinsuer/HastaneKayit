// hasta_kayit_projesi.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include <queue>
#include<vector>
#include<iterator>
#include<list>
using namespace std;

class Insan {
protected:
    string ad;
    int yas;
    bool engelliMi;
public:
    Insan(string ad, int yas,bool engelliMi=false):ad(ad),yas(yas),engelliMi(engelliMi){}
    void yazdir() const {
        cout << "Ad: " << ad << endl;
        cout << "Yas: " << yas << endl;
        cout << "Engellilik durumu: ";
        if (engelliMi)
            cout << "engelli" << endl;
        else cout << "engelli degil" << endl;

    }
};

class Hasta : public Insan {
public:
    int hastaNo;
    int oncelik_puani;
public:

    Hasta(int hastaNo, Insan& i) :hastaNo(hastaNo), Insan(i), oncelik_puani(0) {
        oncelikpuanihesapla();
    }
    Hasta(int hastaNo,string ad, int yas, bool engelliMi=false) : hastaNo(hastaNo),Insan(ad, yas, engelliMi),oncelik_puani(0) {
         oncelikpuanihesapla();
    }

    void oncelikpuanihesapla() {
        if (engelliMi)
            oncelik_puani += 30;
        if (yas > 65)
            oncelik_puani += yas - 65;
    }
    bool operator<(const Hasta& h) const {
        return oncelik_puani < h.oncelik_puani;
    }
    void yazdir() {
        cout << "Hasta No: " << hastaNo << endl;
        Insan::yazdir();
        cout << "Oncelik Puani: " << oncelik_puani << endl;
    }
};

class HastaKayit {
    list<Hasta> kayitSirasi;
    priority_queue<Hasta> muayeneSirasi;
public:
    void kayit(Insan& i) {
        Hasta hasta(kayitSirasi.size()+1, i);
        kayitSirasi.push_back(hasta);
        muayeneSirasi.push(hasta);
    }
    void kayitSirasiYazdir() {
        cout << "*** Hasta kayit sirasi ***" << endl;
        if (kayitSirasi.empty())
            cout << "Kayitli hasta yok" << endl;
        else {
            list<Hasta>::iterator iter = kayitSirasi.begin();
            while (iter != kayitSirasi.end()) {
                Hasta hasta = *iter;
                hasta.yazdir();
                iter++;
                if (iter != kayitSirasi.end()) {
                    cout << endl;
                }
                
            }

        }
        
        cout << "*** Hasta kayit sirasi ***" << endl;
    }
    void MuayeneSirasiYazdir() {
        cout << "*** Muayene sirasi ***" << endl;
        if (kayitSirasi.empty())
            cout << "Muayene bekleyen hasta yok" << endl;
        else {
            priority_queue<Hasta> kuyruk = muayeneSirasi;
            while (!kuyruk.empty()) {
                Hasta hasta = kuyruk.top();
                hasta.yazdir();
                kuyruk.pop();
                if (!kuyruk.empty())
                    cout << endl;
            }

        }

        cout << "*** Muayene sirasi ***" << endl;
    }
    void hastaCagir() {
        
        if (muayeneSirasi.empty()) {
            cout<<endl << "Muayene sirasi icin bekleyen hasta yok" << endl;
        }
        else {
            cout << endl << "Muayeneye cagirilan hasta bilgileri: " << endl;
            Hasta hasta = muayeneSirasi.top();
            hasta.yazdir();
            muayeneSirasi.pop();
        }
    }

};

int main()
{
    Insan insanlar[] = {
        Insan("Ali",30),
        Insan("Veli",35,1),
        Insan("Ayse",70),
        Insan("Fatma",75,1),
        Insan("Mehmet",65,1),
        Insan("Cem",45),
    };
    int elemansayisi = (sizeof insanlar / sizeof * insanlar);
    HastaKayit banko; 
    
    for (int i = 0; i < elemansayisi; i++) {
        banko.kayit(insanlar[i]);

    };
    banko.kayitSirasiYazdir(); cout << endl;
    banko.MuayeneSirasiYazdir(); cout << endl;
    banko.hastaCagir();
    
    
}

// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
