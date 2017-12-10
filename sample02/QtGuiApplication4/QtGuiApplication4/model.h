#pragma once
#include <QObject>
#include <QMap>
#include <QHash>
#include <QList>

class Explorer2 : public QObject {
  Q_OBJECT
    Q_PROPERTY(int id READ id NOTIFY idChanged)
    Q_PROPERTY(float name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QMap<bool, QString> isVisible READ isVisible WRITE setIsVisible NOTIFY isVisibleChanged)
    Q_PROPERTY(char name5 READ name5 WRITE setName5 NOTIFY name5Changed)

  public:
    int id() const { return m_id; }
    float name() const { return m_name; }
    QMap<bool, QString> isVisible() const { return m_isVisible; }
    char name5() const { return m_name5; }

  public slots:
    void setId(const int id) { m_id = id; emit idChanged(); }
    void setName(const float name) { m_name = name; emit nameChanged(); }
    void setIsVisible(const QMap<bool, QString> isVisible) { m_isVisible = isVisible; emit isVisibleChanged(); }
    void setName5(const char name5) { m_name5 = name5; emit name5Changed(); }

  signals:
    void idChanged();
    void nameChanged();
    void isVisibleChanged();
    void name5Changed();

  private:
    int m_id;
    float m_name;
    QMap<bool, QString> m_isVisible;
    char m_name5;
};

class Explorer1 : public QObject {
  Q_OBJECT
    Q_PROPERTY(int id READ id NOTIFY idChanged)
    Q_PROPERTY(QList<QString> name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QMap<bool, QString> isVisible READ isVisible WRITE setIsVisible NOTIFY isVisibleChanged)

  public:
    int id() const { return m_id; }
    QList<QString> name() const { return m_name; }
    QMap<bool, QString> isVisible() const { return m_isVisible; }

  public slots:
    void setId(const int id) { m_id = id; emit idChanged(); }
    void setName(const QList<QString> name) { m_name = name; emit nameChanged(); }
    void setIsVisible(const QMap<bool, QString> isVisible) { m_isVisible = isVisible; emit isVisibleChanged(); }

  signals:
    void idChanged();
    void nameChanged();
    void isVisibleChanged();

  private:
    int m_id;
    QList<QString> m_name;
    QMap<bool, QString> m_isVisible;
};

class Explorer4 : public QObject {
  Q_OBJECT
    Q_PROPERTY(int id READ id NOTIFY idChanged)
    Q_PROPERTY(QList<QString> name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QMap<bool, QString> isVisible READ isVisible WRITE setIsVisible NOTIFY isVisibleChanged)

  public:
    int id() const { return m_id; }
    QList<QString> name() const { return m_name; }
    QMap<bool, QString> isVisible() const { return m_isVisible; }

  public slots:
    void setId(const int id) { m_id = id; emit idChanged(); }
    void setName(const QList<QString> name) { m_name = name; emit nameChanged(); }
    void setIsVisible(const QMap<bool, QString> isVisible) { m_isVisible = isVisible; emit isVisibleChanged(); }

  signals:
    void idChanged();
    void nameChanged();
    void isVisibleChanged();

  private:
    int m_id;
    QList<QString> m_name;
    QMap<bool, QString> m_isVisible;
};

class Explorer3 : public QObject {
  Q_OBJECT
    Q_PROPERTY(int id READ id NOTIFY idChanged)
    Q_PROPERTY(QList<QString> name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QMap<bool, QString> isVisible READ isVisible WRITE setIsVisible NOTIFY isVisibleChanged)

  public:
    int id() const { return m_id; }
    QList<QString> name() const { return m_name; }
    QMap<bool, QString> isVisible() const { return m_isVisible; }

  public slots:
    void setId(const int id) { m_id = id; emit idChanged(); }
    void setName(const QList<QString> name) { m_name = name; emit nameChanged(); }
    void setIsVisible(const QMap<bool, QString> isVisible) { m_isVisible = isVisible; emit isVisibleChanged(); }

  signals:
    void idChanged();
    void nameChanged();
    void isVisibleChanged();

  private:
    int m_id;
    QList<QString> m_name;
    QMap<bool, QString> m_isVisible;
};

class Explorer5 : public QObject {
  Q_OBJECT
    Q_PROPERTY(int id READ id NOTIFY idChanged)
    Q_PROPERTY(QList<QString> name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QMap<bool, QString> isVisible READ isVisible WRITE setIsVisible NOTIFY isVisibleChanged)

  public:
    int id() const { return m_id; }
    QList<QString> name() const { return m_name; }
    QMap<bool, QString> isVisible() const { return m_isVisible; }

  public slots:
    void setId(const int id) { m_id = id; emit idChanged(); }
    void setName(const QList<QString> name) { m_name = name; emit nameChanged(); }
    void setIsVisible(const QMap<bool, QString> isVisible) { m_isVisible = isVisible; emit isVisibleChanged(); }

  signals:
    void idChanged();
    void nameChanged();
    void isVisibleChanged();

  private:
    int m_id;
    QList<QString> m_name;
    QMap<bool, QString> m_isVisible;
};

class AbstractListModel : public QObject {
  Q_OBJECT

  public:

  public slots:

  signals:

  private:
};

