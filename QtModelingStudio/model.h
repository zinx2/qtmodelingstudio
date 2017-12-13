#pragma once
#include <QObject>
#include <QList>

class   Class1 : public QObject {
  Q_OBJECT
    Q_PROPERTY(int pro1_1 READ pro1_1 WRITE setPro1_1 NOTIFY pro1_1Changed)
    Q_PROPERTY(QString pro2_1 READ pro2_1 WRITE setPro2_1 NOTIFY pro2_1Changed)
    Q_PROPERTY(bool pro3_1 READ pro3_1 WRITE setPro3_1 NOTIFY pro3_1Changed)
    Q_PROPERTY(float pro4_1 READ pro4_1 WRITE setPro4_1 NOTIFY pro4_1Changed)

  public:
    int pro1_1() const { return m_pro1_1; }
    QString pro2_1() const { return m_pro2_1; }
    bool pro3_1() const { return m_pro3_1; }
    float pro4_1() const { return m_pro4_1; }

  public slots:
    void setPro1_1(const int pro1_1) { m_pro1_1 = pro1_1; emit pro1_1Changed(); }
    void setPro2_1(const QString pro2_1) { m_pro2_1 = pro2_1; emit pro2_1Changed(); }
    void setPro3_1(const bool pro3_1) { m_pro3_1 = pro3_1; emit pro3_1Changed(); }
    void setPro4_1(const float pro4_1) { m_pro4_1 = pro4_1; emit pro4_1Changed(); }

  signals:
    void pro1_1Changed();
    void pro2_1Changed();
    void pro3_1Changed();
    void pro4_1Changed();

  private:
    int m_pro1_1;
    QString m_pro2_1;
    bool m_pro3_1;
    float m_pro4_1;
};

class   Class2 : public QObject {
  Q_OBJECT
    Q_PROPERTY(int pro1_2 READ pro1_2 WRITE setPro1_2 NOTIFY pro1_2Changed)
    Q_PROPERTY(QString pro2_2 READ pro2_2 WRITE setPro2_2 NOTIFY pro2_2Changed)
    Q_PROPERTY(bool pro3_2 READ pro3_2 WRITE setPro3_2 NOTIFY pro3_2Changed)

  public:
    int pro1_2() const { return m_pro1_2; }
    QString pro2_2() const { return m_pro2_2; }
    bool pro3_2() const { return m_pro3_2; }

  public slots:
    void setPro1_2(const int pro1_2) { m_pro1_2 = pro1_2; emit pro1_2Changed(); }
    void setPro2_2(const QString pro2_2) { m_pro2_2 = pro2_2; emit pro2_2Changed(); }
    void setPro3_2(const bool pro3_2) { m_pro3_2 = pro3_2; emit pro3_2Changed(); }

  signals:
    void pro1_2Changed();
    void pro2_2Changed();
    void pro3_2Changed();

  private:
    int m_pro1_2;
    QString m_pro2_2;
    bool m_pro3_2;
};

class   Class3 : public QObject {
  Q_OBJECT
    Q_PROPERTY(int pro1_3 READ pro1_3 WRITE setPro1_3 NOTIFY pro1_3Changed)
    Q_PROPERTY(QString pro2_3 READ pro2_3 WRITE setPro2_3 NOTIFY pro2_3Changed)
    Q_PROPERTY(bool pro3_3 READ pro3_3 WRITE setPro3_3 NOTIFY pro3_3Changed)
    Q_PROPERTY(float pro4_3 READ pro4_3 WRITE setPro4_3 NOTIFY pro4_3Changed)

  public:
    int pro1_3() const { return m_pro1_3; }
    QString pro2_3() const { return m_pro2_3; }
    bool pro3_3() const { return m_pro3_3; }
    float pro4_3() const { return m_pro4_3; }

  public slots:
    void setPro1_3(const int pro1_3) { m_pro1_3 = pro1_3; emit pro1_3Changed(); }
    void setPro2_3(const QString pro2_3) { m_pro2_3 = pro2_3; emit pro2_3Changed(); }
    void setPro3_3(const bool pro3_3) { m_pro3_3 = pro3_3; emit pro3_3Changed(); }
    void setPro4_3(const float pro4_3) { m_pro4_3 = pro4_3; emit pro4_3Changed(); }

  signals:
    void pro1_3Changed();
    void pro2_3Changed();
    void pro3_3Changed();
    void pro4_3Changed();

  private:
    int m_pro1_3;
    QString m_pro2_3;
    bool m_pro3_3;
    float m_pro4_3;
};

