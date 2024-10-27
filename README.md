# philosopher

**philosopher**, C dilinde yazılmış, "dining philosophers" problemine çözüm sağlayan bir multi-threading simülasyonu. 

## İçerik

- [Özellikler](#özellikler)
- [Kurulum](#kurulum)
- [Kullanım](#kullanım)
- [Algoritma Açıklaması](#algoritma-açıklaması)
- [Debug Format Hakkında](#debug-format-hakkında)

## Özellikler

- Filozoflar arası senkronizasyon ve data race yönetimi.
- Belirtilen süre boyunca yemek yemeleri ve düşünmeleri gereken filozoflar.
- Kullanıcıdan alınan parametrelerle özelleştirilebilen senaryolar.(die durumundan kaçınılmalıdır. İstenen durumlarda die sağlanabilir.)
- "circular" bir masada oturan filozoflar, filozof sayısı kadar fork, ortada bir spagetti kasesi, her filozof yer-uyur-düşünür-ölebilir.
- Data race yönetimi yapılarak önüne geçilir.
- Dead lock durumu engellenir.
- Debug format seçeneği ile smülasyonun nasıl işlediği ayrıntılı çıktı alınarak gözlemlenebilir.
- mutexes kullanımı
- multi-threading yönetimi

## Kurulum

Bu projeyi kendi bilgisayarınızda çalıştırmak için aşağıdaki adımları izleyin:

1. Projeyi klonlayın:
   ```bash
   git clone https://github.com/kullanıcı_adı/philosopher.git
2. "philo" dosyasına girin:
   ```bash
   cd philo
3. Derleyin:
   ```bash
   make

## Kullanım

Projeyi çalıştırmak için terminalde aşağıdaki komutu kullanın:
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
(Son arg ([number_of_times_each_philosopher_must_eat]) opsiyoneldir.)

Örneklersek;
```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
```
şeklinde deneyip gözlemleyebilirsiniz.

## Algoritma Açıklaması

Her filozofun bir çatal (fork) ile yemek yemesi gerekmektedir. Belirtilen süre içinde yiyemeyen filozoflar ölür. Ancak ölümden kaçınılması gerekiyor.

Filozoflar kendi çatallarını ve bir sonraki filozofun çatalını (sağ sol) alabilir.

Eğer bir filozof bir çatalı alamazsa, diğer çatalı bekler.(thinking) (Bu durum, filozofların birbirleriyle senkronize bir şekilde yemek yemesi için önemlidir.)

Bu simülasyon, mutexes kullanarak gerçekleştirilmiştir.

## Debug Format Hakkında

"philo.h" kütüphanesine giderek "DEBUG_FORMATTING" makrosunun değerini "1" yaptıktan sonra tekrar derlerseniz simülasyonun ayrıntılı işleyişini görebilirsiniz.
