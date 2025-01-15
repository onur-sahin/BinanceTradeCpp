# MVVM-C Yapısında Bileşenlerin Sorumlulukları

---

## 1. Model

Model, uygulamanın verilerini ve iş mantığını içerir. Genellikle veritabanı, API çağrıları, iş kuralları ve veri üzerinde işlem yapma gibi görevleri üstlenir.

### Sorumlulukları
- Uygulamanın veri yapısını ve iş mantığını tanımlar.
- Veritabanı işlemlerini yönetir (CRUD işlemleri gibi).
- İş mantığına uygun veriyi sağlar, işlemleri yürütür ve gerektiğinde sonuçları döner.

### Örnekler
  - `DBManager` sınıfı, bir kullanıcıyı veri tabanına eklemek veya silmek için metotlar içerir:

    ```cpp
    class DBManager {
    public:
        bool addUser(const QString &username, const QString &password);
        bool deleteUser(int userId);
    };
    ```

  - `LoginModel` sınıfı, kullanıcı bilgilerini doğrulamak için bir işlev sağlar:

    ```cpp
    class LoginModel {
    public:
        bool validateCredentials(const QString &username, const QString &password);
    };
    ```

---

## 2. ViewModel

ViewModel, Model ile View arasındaki köprü görevi görür. Model'den verileri alır, işler ve View’a sunar. Aynı zamanda kullanıcı etkileşimlerinden gelen olayları Model’e yönlendirir.

### Sorumlulukları
- Model'den aldığı verileri işleyip View'a uygun hale getirir.
- View'dan gelen kullanıcı etkileşimlerini Model'e iletir.
- View’a sağladığı verilerin güncellenmesini dinler ve gerektiğinde View’ı günceller.
- Coordinator ile iletişim kurarak, View’da gerekli geçişlerin yapılması veya yeni pencerelerin açılması talebinde bulunabilir.

### Örnekler
  - ViewModel, Model'den aldığı kullanıcı listesini işleyip View’a sunar:

    ```cpp
    class UserViewModel : public QObject {
    public:
        UserViewModel(UserModel* model);
        QStringList getUsernames();
    };
    ```

  - **Sinyal İletişimi**: Kullanıcı giriş yaptıktan sonra Coordinator'a bir sinyal gönderir:

    ```cpp
    class LoginViewModel : public QObject {
        Q_OBJECT
    public:
        LoginViewModel(LoginModel* model);

    signals:
        void loginSuccessful();
        void loginFailed();

    public slots:
        void attemptLogin(const QString &username, const QString &password) {
            if (model->validateCredentials(username, password)) {
                emit loginSuccessful(); // Coordinator'a bildirim
            } else {
                emit loginFailed();
            }
        }
    };
    ```

---

## 3. View

View, kullanıcı arayüzünü temsil eder ve kullanıcıdan gelen etkileşimleri alır. Ancak iş mantığını içermez; yalnızca görüntüleme ve kullanıcı girişlerini almakla ilgilenir.

### Sorumlulukları
- Kullanıcıya arayüzü sağlar ve girişlerini alır.
- Görselleştirme ile ilgili tüm işlemleri yürütür (butonlar, etiketler, listeler vb.).
- ViewModel’den gelen veriyi görüntüler ve ViewModel’e kullanıcı etkileşimlerini iletir.
- Görsellik, düzen ve arayüz mantığını içerir ancak veri işleme yapmaz.

### Örnekler
  - **Kullanıcı Etkileşimleri**: `LoginView`, kullanıcı giriş bilgilerini alır ve ViewModel’e iletir.

    ```cpp
    class LoginView : public QWidget {
        Q_OBJECT
    public:
        LoginView() {
            // Kullanıcı giriş bilgileri için widget'ları kurma
        }

    signals:
        void loginButtonClicked(const QString &username, const QString &password);
    };
    ```

  - **Veriyi Görüntüleme**: Kullanıcı bilgilerini ViewModel’den alır ve gösterir:

    ```cpp
    void LoginView::displayMessage(const QString &message) {
        messageLabel->setText(message);
    }
    ```

---

## 4. Coordinator

Coordinator, ekranlar arasında geçişleri ve kullanıcı akışını yönetir. Coordinator'lar, View ve ViewModel nesnelerini yaratır, yönlendirir ve View’ın ne zaman gösterileceğine karar verir.

### Sorumlulukları
- View, ViewModel ve Model nesnelerini yaratıp ilişkilendirir.
- Ekranlar arasındaki geçişleri kontrol eder (örneğin, giriş başarılı olduğunda ana ekrana geçiş).
- ViewModel’den gelen sinyalleri dinler ve View’ı gerektiğinde günceller veya başka bir koordinatöre geçiş yapar.

### Örnekler
  - **Pencere Gösterme**: Login işlemi başarılı olursa ana ekranı açar.

    ```cpp
    class LoginCoordinator : public QObject {
        Q_OBJECT
    public:
        LoginCoordinator() {
            loginView = new LoginView();
            loginViewModel = new LoginViewModel(new LoginModel());

            connect(loginView, &LoginView::loginButtonClicked, loginViewModel, &LoginViewModel::attemptLogin);
            connect(loginViewModel, &LoginViewModel::loginSuccessful, this, &LoginCoordinator::showMainView);

            loginView->show();
        }

    private slots:
        void showMainView() {
            mainView = new MainVw();
            mainView->show();
            loginView->close();
        }
    };
    ```

  - **Koordinatörler Arası Geçiş**: `MainCoordginCoordinator` ve `UserCoordinator` arasında geçiş yapabilir:

    ```cpp
    class MainCoord {
    public:
        MainCoord() {
            loginCoordinator = new LoginCoordinator();
            connect(loginCoordinator, &LoginCoordinator::loginCompleted, this, &MainCoord::showUserCoordinator);
        }

    private slots:
        void showUserCoordinator() {
            userCoordinator = new UserCoordinator();
            userCoordinator->start();
        }
    };
    ```

---

## Özetleyici Notlar

Bu yapıda:
- **Model** veriyi ve iş mantığını yönetir, View veya Coordinator ile doğrudan iletişime geçmez.
- **ViewModel**, Model’den veriyi alır, işler ve View’a sunar; ayrıca kullanıcı etkileşimlerini alıp Model’e aktarır.
- **View** yalnızca kullanıcı arayüzünden sorumludur; veri üzerinde işlem yapmaz, kullanıcı etkileşimlerini alır ve ViewModel’e iletir.
- **Coordinator** UI akışını kontrol eder, ekrana hangi pencerelerin getirileceğine karar verir ve ViewModel sinyalleri üzerinden akışa yön verir.

Bu yapı, sorumlulukların net bir şekilde ayrılmasını sağlayarak, uygulamanın daha modüler, test edilebilir ve bakımı kolay olmasına yardımcı olur.
