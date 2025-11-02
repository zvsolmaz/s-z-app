# 🧾 ReYeTaP - Restaurant Food Order Tracking Project

**Programming II Term Project – Developed in C Language**

A C-based project simulating a full restaurant management system including food orders, kitchen operations, and managerial reporting.

---

## 📌 Project Overview

**ReYeTaP** is a modular restaurant food ordering and management system written in C. It is composed of three distinct applications:

- `Musteri.exe` – Customer-facing food ordering system  
- `Restoran.exe` – Admin panel for management and analytics  
- `Mutfak.exe` – Kitchen operations with preparation queue logic  

---

## 🔧 Application Components

### ✅ 1. Musteri.exe (Customer Interface)

- 📥 **New Order**  
  Reads available dishes from `yemeklistesi.txt` and saves orders to `siparisler.txt`.  
  Only available meals are listed.

- 🔎 **Order Status**  
  Displays live order details: ordered items, total cost, and time left for preparation.

- 📜 **Order History**  
  Shows all completed past orders belonging to the logged-in user.

---

### ✅ 2. Restoran.exe (Admin Panel)

- 🍽 **Meal Management**  
  Add, update, or remove meals directly within `yemeklistesi.txt`.

- ✔️❌ **Approve / Reject Orders**  
  Interact with new customer orders and route approved ones to `Mutfak.exe`.

- 📊 **Daily Report**  
  Save and retrieve logs filtered by date to avoid `siparisler.txt` bloat.

- 📈 **Analytics**  
  - Daily / Monthly / Periodic earnings  
  - Most popular dish  
  - Most profitable day  
  - Top customer (by order count)

---

### ✅ 3. Mutfak.exe (Kitchen Processing)

- 🧑‍🍳 **Chef Scheduling System**  
  Calculates preparation time based on chef availability. Each chef can only prepare one meal at a time using a queueing system.

---

## 📁 File Structure

```plaintext
.
├── yemeklistesi.txt        # Meal data: name, price, duration, availability
├── siparisler.txt          # All recorded orders (pending and completed)
├── Musteri.exe             # Customer interface
├── Restoran.exe            # Admin interface
├── Mutfak.exe              # Kitchen automation logic
```

---

## 🧪 Example Data

### yemeklistesi.txt
```plaintext
Yemek Adı        | Fiyat   | Süre (dk) | Durum
-----------------|---------|-----------|---------
Lahmacun         | 75 TL   | 20        | Mevcut
Hamburger        | 250 TL  | 30        | Mevcut
Mantı            | 160 TL  | 45        | Mevcut_Degil
```

### siparisler.txt
```plaintext
SiparişID        | Yemek      | Fiyat   | Sipariş Zamanı     | Hazırlık Zamanı     | Kullanıcı | Aşçı
SIP010424_001    | Lahmacun   | 75 TL  | 01.04.2024 - 10:00 | 01.04.2024 - 10:20  | user1     | A1
```

---

## ⚙️ Technologies & Structure

- Language: `C`
- File I/O: `fopen`, `fscanf`, `fprintf`
- Modular programming: small reusable functions
- Clean, indented and well-commented source code
- ID generation logic for orders

---


---

# 🧾 ReYeTaP - Restoran Yemek Takip Projesi

**Programlama II Dönem Projesi – C Dili ile Geliştirilmiştir**

C dili ile geliştirilmiş restoran sipariş yönetim sistemi; müşteri, restoran ve mutfak olmak üzere 3 ana uygulamadan oluşur.

---

## 📌 Proje Hakkında

**ReYeTaP**, yemek siparişi, mutfak yönetimi ve analiz işlemlerini kapsayan bir restoran takip sistemidir. Uygulama bileşenleri şunlardır:

- `Müşteri.exe` – Müşteri tarafından sipariş verilmesini sağlar  
- `Restoran.exe` – Yönetici paneli ve analiz işlemleri  
- `Mutfak.exe` – Aşçı ve hazırlama süresi hesaplama sistemi  

---

## 🔧 Uygulama Bileşenleri

### ✅ 1. Müşteri.exe

- 📥 **Yeni Sipariş Verme**  
  `yemeklistesi.txt` dosyasından mevcut yemekleri gösterir, `siparisler.txt` dosyasına kayıt yapar.

- 🔎 **Sipariş Durumu**  
  Mevcut siparişin detaylarını gösterir (içerik, fiyat, süre vb.).

- 📜 **Geçmiş Siparişlerim**  
  Önceki tamamlanmış siparişleri kullanıcı bazlı listeler.

---

### ✅ 2. Restoran.exe

- 🍽 **Yemek Ekle / Sil / Güncelle**  
  Menüdeki yemekler `yemeklistesi.txt` üzerinden düzenlenebilir.

- ✔️❌ **Sipariş Onaylama / Reddetme**  
  Yeni siparişler yönetilir, `Mutfak.exe`'ye gönderilir.

- 📊 **Günlük Rapor**  
  `siparisler.txt` boyutunu sınırlamak için günlük kayıtlar ayrı dosyaya aktarılır.

- 📈 **Analiz Özellikleri**  
  - Günlük / Aylık / Dönemsel Kazanç  
  - En çok sipariş verilen yemek  
  - En kârlı gün  
  - En çok sipariş veren kullanıcı

---

### ✅ 3. Mutfak.exe

- 🧑‍🍳 **Aşçıya Göre Hazırlama Süresi**  
  Her aşçı yalnızca bir yemek hazırlayabilir. Kuyruk yönetimi ile yemek süreleri planlanır.

---

## 📁 Dosya Yapısı

```plaintext
.
├── yemeklistesi.txt        # Yemeklerin adı, fiyatı, süresi, durumu
├── siparisler.txt          # Siparişlerin kayıt altına alındığı dosya
├── Müşteri.exe             # Müşteri arayüzü
├── Restoran.exe            # Yönetici arayüzü
├── Mutfak.exe              # Mutfak otomasyon uygulaması
```

---

## 🧪 Örnek Dosya İçeriği

### yemeklistesi.txt
```plaintext
Yemek Adı        | Fiyat   | Süre (dk) | Durum
-----------------|---------|-----------|---------
Lahmacun         | 75 TL   | 20        | Mevcut
Hamburger        | 250 TL  | 30        | Mevcut
Mantı            | 160 TL  | 45        | Mevcut_Değil
```

### siparisler.txt
```plaintext
SiparişID        | Yemek      | Fiyat   | Sipariş Zamanı     | Hazırlık Zamanı     | Kullanıcı | Aşçı
SIP010424_001    | Lahmacun   | 75 TL  | 01.04.2024 - 10:00 | 01.04.2024 - 10:20  | user1     | A1
```

---

## ⚙️ Teknik Bilgiler

- Geliştirme Dili: `C`
- Kullanılan Fonksiyonlar: `fopen`, `fscanf`, `fprintf`
- Sipariş ID'leri otomatik oluşturulur
- Fonksiyonel ve modüler yapı

Proje      : ReYeTaP - Restoran Yemek Takip Sistemi
```
