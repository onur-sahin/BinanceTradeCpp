``` cpp
std::exception
    |
    |-- std::bad_alloc             (Bellek tahsis edilemedi)
    |-- std::bad_array_new_length  (Array new için geçersiz uzunluk)
    |-- std::bad_cast              (Geçersiz tip dönüştürme)
    |-- std::bad_exception         (Beklenmeyen bir hata yakalama)
    |-- std::bad_function_call     (Geçersiz işlev çağrısı)
    |-- std::bad_typeid            (Geçersiz tipid, typeid kullanımı sırasında)
    |-- std::bad_weak_ptr          (weak_ptr ile geçersiz referans)
    |-- std::logic_error           (Mantıksal hatalar)
    |     |-- std::invalid_argument    (Geçersiz argüman)
    |     |-- std::domain_error        (Geçersiz aralık veya alan)
    |     |-- std::length_error        (Geçersiz uzunluk)
    |     |-- std::out_of_range        (Geçersiz aralık)
    |
    |-- std::runtime_error         (Çalışma zamanı hataları)
          |-- std::range_error         (Aralık hatası)
          |-- std::overflow_error      (Taşma hatası)
          |-- std::underflow_error     (Alt taşma hatası)
    |
    |-- std::system_error          (Sistem hataları)
    |     |-- std::ios_base::failure   (Giriş/çıkış işlemlerindeki hatalar)
    |
    |-- std::future_error          (Concurrency ile ilgili hatalar)
    |
    |-- std::bad_variant_access    (std::variant ile geçersiz erişim)

```

# C++ Hata Sınıfları Açıklamaları

## std::exception
C++ standart kütüphanesinde tanımlı tüm hata sınıflarının temel sınıfıdır. Bu sınıf, hata mesajlarını döndürmek için kullanılan `what()` sanal fonksiyonunu sağlar. Hata yönetimi için temel bir yapı sağlar ve kullanıcı tanımlı hata sınıflarının türetilmesine olanak tanır.

## std::bad_alloc
Bellek tahsis edilemediğinde fırlatılan bir hata sınıfıdır. Genellikle `new` operatörü kullanılırken karşılaşılan bu hata, bellekte yeterli alan kalmadığında ortaya çıkar. Kullanıcıların bellek yönetimini dikkatli bir şekilde yapmaları gerektiğini belirtir.

## std::bad_array_new_length
`new` operatörü kullanılarak oluşturulacak bir dizi için geçersiz bir uzunluk belirtildiğinde fırlatılan hatadır. Bu durum, dizinin boyutunun sıfır veya negatif bir değer olduğu durumlarda ortaya çıkar ve genellikle programın mantığında bir hata olduğunu gösterir.

## std::bad_cast
Geçersiz bir tip dönüştürme (cast) işlemi sırasında fırlatılır. Özellikle `dynamic_cast` kullanıldığında, nesne türünün beklenenden farklı olması durumunda bu hata meydana gelir. Kullanıcıların tür güvenliğine dikkat etmeleri gerektiğini belirtir.

## std::bad_exception
Beklenmeyen bir hata yakalandığında fırlatılan hatadır. Bu sınıf, beklenmeyen durumlarla karşılaşıldığında kullanıcının hata yönetimini sağlamasına yardımcı olur. Genellikle kullanıcı tanımlı hataların işlenmesi için kullanılır.

## std::bad_function_call
Geçersiz bir işlev çağrısı yapıldığında fırlatılan bir hata sınıfıdır. Bu durum, çağrılan işlevin geçersiz bir bağlamda veya yanlış bir şekilde çağrılması sonucunda ortaya çıkar.

## std::bad_typeid
`typeid` operatörü kullanıldığında, geçersiz bir tip ID'si alındığında fırlatılan hatadır. Özellikle polymorphism (çok biçimlilik) durumlarında, sınıf hiyerarşisinin düzgün bir şekilde oluşturulmadığı durumlarda ortaya çıkar.

## std::bad_weak_ptr
`weak_ptr` ile geçersiz bir referans almaya çalışıldığında fırlatılan bir hatadır. `weak_ptr` kullanarak paylaşılan nesneleri izlerken, nesnenin varlığını kontrol etmenin önemli olduğunu belirtir.

## std::logic_error
Programın mantığında oluşan hatalar için kullanılır. Derleme zamanında tespit edilebilecek hatalar genellikle bu sınıfa girer. Kullanıcıların mantıksal hataları tespit etmelerine ve düzeltmelerine yardımcı olur.

### Alt Sınıfları:
- **std::invalid_argument**: Geçersiz bir argüman hatası olduğunda fırlatılır. Fonksiyonlara geçirilen argümanların uygun olmadığını belirtir.
- **std::domain_error**: Matematiksel işlemlerde geçersiz bir alan kullanıldığında fırlatılır. Örneğin, negatif bir sayı için karekök alma işlemi.
- **std::length_error**: Bir nesneye veya diziye verilen boyut geçerli aralığın dışındaysa fırlatılır. Kullanıcıların dizi boyutlarına dikkat etmelerini vurgular.
- **std::out_of_range**: Geçersiz bir dizi indeksi veya anahtar kullanımı durumunda ortaya çıkar. Dizi sınırlarını aşmaya çalıştığınızda bu hata fırlatılır.

## std::runtime_error
Program çalışırken oluşan hatalar için kullanılır. Genellikle dinamik olarak fırlatılan hatalar bu kategoriye girer. Hataların çalışma zamanı sırasında meydana geldiğini belirtir.

### Alt Sınıfları:
- **std::range_error**: Matematiksel bir işlem sırasında oluşan aralık hatasıdır. Hesaplama sırasında geçersiz bir aralık kullanımı durumunda fırlatılır.
- **std::overflow_error**: Bir işlem sırasında bir sayının taşması durumunda ortaya çıkar. Örneğin, `int` türünün sınırlarının aşılması.
- **std::underflow_error**: Bir işlem sırasında bir sayının alt taşması (örneğin, çok küçük bir sayıya ulaşma) durumudur.

## std::system_error
Sistemle ilgili hataları temsil eder. Örneğin, dosya giriş/çıkış hataları gibi durumlarda kullanılır. Sistem hatalarını yönetmek için yapı sağlar.

### Alt Sınıfı:
- **std::ios_base::failure**: Giriş/çıkış işlemleri sırasında oluşabilecek hataları temsil eder. Dosya açma, okuma veya yazma işlemlerinde başarısızlık durumunda fırlatılır.

## std::future_error
Çoklu iş parçacığı (concurrency) ile ilgili hataları temsil eder. Gelecekteki sonuçları yönetirken oluşabilecek hataları işlemek için kullanılır.

## std::bad_variant_access
`std::variant` türünden geçersiz bir erişim durumunda fırlatılan bir hata sınıfıdır. `std::variant` kullanarak bir türü temsil ederken, yanlış türle erişmeye çalıştığınızda bu hata meydana gelir.

