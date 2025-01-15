
class QCloseEvent;

class IMainVw{

public:

    virtual ~IMainVw()   =default;
    virtual void show_window(bool status) = 0;
    virtual void set_enabled(bool enabled) = 0;
    virtual void closeEvent(QCloseEvent *event) = 0;

private:



};