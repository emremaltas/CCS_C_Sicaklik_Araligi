# Sıcaklık Sensörü
29.07.2021
Kullanıcı "Sıcaklıkları Ayarla"butonuna bastığında,kullanıcıdan(Timer0 sayıcı olarak kullanılmıştır.)3 adet 2 ile 150 C' arasinda sıcaklık girmesi isteniyor.Programda aralık dışındaki girişler engellenmiştir.
Alınan bu 3 sıcaklik değeri sonradan yeniden değiştiriebiliyor.
Alınan sıcaklık değerleri küçükten büyüğe sıralanıyor.
Ardından ölçülen sıcaklık değerleri ,girilen bu sıcaklık değerleri ile karşılaştırılıyor.
Eğer ölçülen sıcaklık,kullanıcıdan alınan sıcaklık değerinin en küçüğünden küçük ise "MAVİ LED",küçük ile ortanca değer arasında ise "SARI LED",ortanca ve büyük değer aralığında ise "YEŞİL LED",girilen en büyük değerden de büyük ise "KIRMIZI LED" yanıyor.
Anlık sıcaklık değeride TIMER1 kesmesi ile LCD ekranında gösteriliyor.(Zamanlayıcı olarak kullanılmıştır.)
"Dereceleri Göster" butonuna basıldığında girilen sıcaklık değerleri küçükten büyüğü LCD ekranında gösteriliyor.


