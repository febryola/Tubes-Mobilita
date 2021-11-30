# Tubes MOBILITA
This project is maintained by 5 people :
|Nama  | NIM|
   | ----- | ------------ | 
  |Alifia Rahmah   |   13520122     |  
 | Jevant Jedidia Augustine  |    13520133    |  
 |Febryola Kurnia Putri |     13520140   |  
  |Vito Ghifari |    13520153   |  
   |Willy Wilsen |     13520160    |  
   
## What is this project about?
   Projek ini dibuat bertujuan untuk memenuhi tugas besar mata kuliah IF2110, Algoritma dan Struktur Data.
   Tugas ini merupakan implementasi dari materi yang telah dipelajari di kelas yaitu implementasi ADT pada program
   yang meliputi materi ADT point, list statis, list dinamis, matrix, mesin kata, mesin karakter, queue, stack, 
   linked list, dan ADT lain yang diperlukan.
   
## Deskripsi Program
   Program ini mensimulasikan seorang kurir, yaitu mobilita yang sedang mengalami kesulitan di masa pandemi sehingga
   mengharuskan dia menjadi kurir untuk membantu orang tuanya. Program ini akan membantu mobita dalam mengantarkan
   barang kepada pelanggan, mulai dari proses pemesanan, pengambilan, pengantaran, hingga penerimaan, serta lokasi
   dari setiap barang dan pelanggan. ADT yang telah diimplementasikan sebelumnya digunakan pada program ini, mulai dari
   proses membeli, dropoff, pickup, progress pengantaran, antrian barang yang harus diantarkan, hingga barang mana yang
   harus didahulukan untuk diantarkan kepada pelanggan semua terdapat pada program ini.
   
## Bahasa
   Bahasa yang digunakan adalah bahasa C
   
## Setup Penggunaan
   pastikan GCC sudah terinstall
   * Windows
      1. Unduh [Make for Windows](http://gnuwin32.sourceforge.net/downlinks/make.php)
      2. Jalankan setup, catat folder tempat instalasi GnuWin32
      3. Tambahkan folder `bin` dari installation folder GnuWin32 ke [Path dalam Environment Variables Windows](https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/)
      4. Jalankan perintah berikut pada Windows Powershell/Command Prompt
   ```
   > make
   > ./main.exe
   ```
   
   * Linux
      <br>Jalankan perintah berikut pada terminal
   ```
   $ make
   $ ./main.exe
   ```

## Pembagian Kerja
   |Nama  | NIM| Deskripsi Kerja|
   | ----- | ------------ | --------------- |
  |Alifia Rahmah   |   13520122     |  Merencanakan dan mengimplementasikan command BUY,PICK_UP, RETURN|
 | Jevant Jedidia Augustine  |    13520133    |  Membuat main menu(new game dan exit), modifikasi mesin kata, merencanakan dan mengimplementasikan command MAP |
 |Febryola Kurnia Putri |     13520140   |  Membentuk ADT baru untuk type gadget, item, dan command TO_DO |
  |Vito Ghifari |    13520153   |  Merencanakan dan mengimplementasikan command IN_PROGRESS,MOVE,HELP |
   |Willy Wilsen |     13520160    | Merencanakan dan mengimplementasikan command DROP_OFF, INVENTORY, efek VIP item |
   
## Status Tubes
   finished
   
