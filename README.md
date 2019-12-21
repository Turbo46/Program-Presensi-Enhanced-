# Program Presensi (Enhanced)
## Penyusun
Kelompok 1

Alvin Audinata (1806200204)

Gilbert Parluhutan Siagian (1806148681)

## Selayang Pandang

"Program Presensi (Enhanced)", selanjutnya disebut "Program", dibuat sebagai alat bantu yang dapat digunakan oleh dosen/fasilitator dalam pencatatan presensi (kehadiran) terhadap mahasiswanya pada suatu mata kuliah tertentu. Lebih khususnya, Program ini diperuntukkan untuk dosen/fasil yang belum menerapkan sistem presensi berbasis komputer untuk sebagian/seluruh mata kuliah yang diampunya. Harapannya, dengan menggunakan Program ini sebagai alat presensi di kelas, data-data kehadiran mahasiswa lebih terkomputerisasi dan lebih mudah untuk dikelola. Selain itu, juga dapat meminimalisir kesalahan yang dibuat saat presensi berlangsung.

## Perubahan dari Versi Sebelumnya

Versi dari Program merupakan pengembangan prototipe Program ini pada [versi sebelumnya](https://github.com/Turbo46/Program-Presensi-Dosen). Terdapat beberapa tambahan fitur pada versi ini, yang tidak terdapat pada versi sebelumnya:

1. ***User-friendly*** Versi ini menggunakan Win32 API, Program memiliki tampilan dan cara kerja selayaknya program-program pada umumnya, dibandingkan versi sebelumnya yang masih menggunakan *command-line interface* (CLI), sehingga lebih mudah digunakan.
2. ***Penggunaan Visual Studio*** sebagai *compiler* dan *builder* Program ini, membuat Program lebih *powerful* dari segi teknis maupun user interface. Selain itu, proses *debug* pun lebih mudah dilakukan, karena tidak semua objek pada Program dalam bentuk *code*, melainkan ada yang berupa gambar dan objek sehingga tidak perlu mengubah seluruh *code* ketika hanya ingin mengubah tampilannya saja.
3. ***Penggunaan linked list dalam pengelolaan data mahasiswa*** menjadikan memori Program dialokasikan secara dinamis (sesuai kebutuhan), sehingga memori yang digunakan relatif kecil, hanya sekitar 2MB saja. Selain itu, tidak perlu melakukan looping untuk mencari dan mengubah data seiring berjalannya aplikasi, melainkan hanya perlu *reference* ke alamat lokasi data dimaksud kemudian secara langsung mengubah data pada lokasi tersebut, membuat Program berjalan lebih cepat.

## Fitur Utama

1. ***Tampilan yang user-friendly*** membuat Program dapat dipakai oleh tenaga pengajar dari berbagai kalangan.

2. ***Memungkinkan dosen untuk input matkul secara mandiri*** Fleksibel, mata kuliah ("matkul") yang dimasukkan dapat disesuaikan dengan kebutuhan dosen. Jika ada yang sudah tidak dibutuhkan, matkul tersebut dapat dihapus untuk mempermudah pengelolaan.

3. ***Proteksi presensi lapis ganda*** mencegah dosen melakukan presensi di luar jam kuliah atau di luar periode kuliah, sehingga kesalahan akibat ketidaksengajaan atau tangan orang lain dapat diminimalisasi.

4. ***Rekapitulasi data*** Setelah minimal melakukan satu kali presensi di sebuah mata kuliah, dosen dapat melihat rekap presensi kelas tersebut per mahasiswa, bahkan menentukan dapat/tidaknya mahasiswa tersebut mengikuti ujian (Baik UTS maupun UAS).

5. ***Tidak memakan memori besar juga reponsif*** dengan alokasi memori dinamik dan penggunaan *linked list*.

## Menggunakan Program

Untuk dapat menggunakan Program, unduh *repository* ini dalam bentuk ZIP, kemudian extract ke folder tertentu.

### Secara langsung

Setelah Program di-extract, jalankan Program secara langsung dengan membuka "Final Project Proglan.exe" melalui:

```
[Direktori Program] -> Final Project Proglan -> Final Project Proglan -> Final Project Proglan.exe
```

### Menggunakan Microsoft Visual Studio dan Melihat Kode Sumber

Untuk melakukan hal ini, pastikan komputer Anda sudah terpasang Microsoft Visual Studio versi terbaru. Jika belum, unduh [di sini](https://visualstudio.microsoft.com/), kemudian lakukan pemasangan sesuai prosedur yang ada. Anda boleh mengubah pengaturan standar, tetapi memasang dengan pengaturan standar juga tidak masalah.

Setelah pemasangan selesai, buka *file* solusi Program melalui:

```
[Direktori Program] -> Final Project Proglan -> Final Project Proglan.sln
```
