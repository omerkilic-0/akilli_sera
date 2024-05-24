
# Akıllı Sera

Bu proje 2023-2024 yılında Tavşanlı MYO Bilgisayar Programcılığı Programı Mikroişlemciler dersin Kadir Ocak, Ömer Kılıç ve Kerim Sarı isimli 3 öğrenci tarafından geliştirilmiştir. 

Proje temel olarak elektrik ihtiyacını güneş paneli sayesinde yenilenebilir enerjiden sağlayarak çalışmakta olup, sulama ve havalandırma işlemlerini tamamen otonom olarak gerçekleştirebilmektedir. Aynı zamanda geliştirilen Mobil Uygulama sayesinden canlı veriler görüntülenebilir ve sera kontrol edilebilir durumda olacaktır.

# Projeyi Hayata Geçirme

Gerekli olan komponentleri tedarik ettikten sonra adımları takip ederek projeyi çalışabilir hale getirebilirsiniz.

## 1. Adım - Komponentler

### Kullanılan Teknolojiler

**İstemci:** Arduino Ekosistemi, ESP32 geliştirme kartı

**Sunucu:** FireBase, MIT APP INVENTOR

## Komponentler

- Ardunio UNO
- 2x16 LCD Ekran
- Mini Dalgıç Su Pompası
- DHT11 Sıcaklık ve Nem Sensörü
- Toprak Nem Sensörü | 2 adet
- BradeBorad | Orta Boy
- ESP32 wroom | Dev Modül
- 10K Potansiyometre
- Ortec 25W Güneş Paneli
- Akü Şarj Cihazı PWM Marka
- 12V 7A Akü
- Erkek-Erkek Jumper | 40 Adet
- Dişi-Dişi Jumper | 40 Adet
- Dişi-Erkek Jumper | 80 Adet
- 10K Direnç | 10 Adet
- LDR Işık Sensörü
- Push Buton | 3 Adet
- Switch Buton | 2 Adet
- 5V Röle | 3 Adet
- Buzzer
- Kırmızı LED
- Fan
- UV LED
- Şipşak Anahtar
- Su Hortumu
- Kablo Kanalı | 35cm
- Lehim Teli
- Havya
- 
## 2. Adım - Devreyi Kurma

Devre şemasına bağlı kalarak devreyi kurun. Kırmızı renk (+) ve siyah renk (-)' yi temsil etmektedir.

![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/fd166ca9-57d8-40f2-a569-399c1979cb63)

## 3. Adım - FireBase' yi oluşturun

Gösterildiği dizinde Web API' nizi oluşturun.

```
FireBase
├── bMod
├── dDOrani
├── fan
├── gMiktari
├── hIsisi
├── hINem
├── kontrol
├── led
├── sDurumu
└── tNOrani
```

![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/41c1986d-005b-42bc-a8ce-817e43846d97)

## 4. Adım - Kodu Yazma

FireBase nizi oluşturduktan sonra ESP32 kodu üzerinde "..." olarak bırakılan bölgeye WİFİ adı ve Şifreiniz daha sonra FireBase URL ve Şifrenizi yazın.

Arduino yu bilgisayrınıza bağladıktan Arduino İde aracılığı ile Board ve Port ayarlarını yaparak arduino.ino kodunu yazın.

ESP32 yi bilgisayrınıza bağladıktan sonra Arduino İde aracılığı ile gerekli Driverleri kurduktan sonra Board ve Port ayarlarını yaparak esp32.ino kodunu yazın.

## 5. Adım - Mobil Uygulamayı Hazırlama

MIT APP Inventor ile hazırlamış olduğumuz Mobil Uygulamamızın görselleri alt kısımda bulunmaktadır. Kendi zevkinize göre tasarlayabilir veya mobil.apk dosyası üzerinden uygulamamıza göz atabilirsiniz.

### Açılış Sayfası
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/07264227-e988-496c-826e-1ff2897a5cf0)
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/26a822b9-ee17-4212-9068-e2f419b03bc1)

### Ana Sayfa
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/ce6203d2-6172-4908-b766-b56a8aa867c6)
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/ae3cdf33-61f1-4854-91b8-24df95ddfe73)

### Kontrol Paneli
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/e5a5f358-953b-4da3-aa5f-94afd3ab58f3)
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/b0a0665f-19b5-4483-901a-177d829c660e)

# Kapanış

Tebrikler. Tüm adımları uyguladınız ve Akıllı Seranız aktif olarak çalışmaktadır. Fakat bu projenin konsept bir proje olduğu unutulmamalı ve geliştirilebilecek birçok noktası bulunduğunu unutmayın. Eğer projemize katkıda bulunur iseniz çok sevinizir.

## Sera Genel Görüntüsü
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/f8563015-0091-44c0-a7c5-8e52aa91af56)

## Küç Kaynağı Sistemi
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/812472b0-e3e1-4419-8737-1b3ccf3089d1)
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/a78cf083-f650-4883-a699-f4f588238117)

## Sensörler ve Motorlar
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/7a6b23ec-a407-4d7e-8dcc-142004a32daf)
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/8c05b392-df80-4ad4-b56e-00890c7461b0)
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/0561f49b-93a7-4bb1-bf0c-8ba8d126e6bf)
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/bfebacca-c2f5-48f9-bac6-332709455302)

## Kontrol Paneli
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/7de52d6c-d24f-45c4-a2ff-f23b09509a4e)
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/5fa2d457-3979-4ad7-9c23-3d92d2a49e8e)
![image](https://github.com/omerkilic-0/akilli_sera/assets/123635257/06a474e5-c62b-4c21-a393-695d74fefdea)

## geliştirilebilecek Noktalar

- Mobil Uygulama ile sera yönetim işlemleri eklenebilir. 
- Seranın veya Mobil Uygulamanın UI ve UX geliştirilmesi yapılabilir.
