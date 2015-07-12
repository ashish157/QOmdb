/*************************************************************************************
** The MIT License (MIT)
**
** Qt/QML wrapper around The Open Movie Database API
** Copyright (c) 2015 Ashish Dabhade
** Email: ashishd157@gmail.com
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
************************************************************************************/

#ifndef QOMDB_H
#define QOMDB_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaEnum>

template<typename E>
constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type
{
   return static_cast<typename std::underlying_type<E>::type>(e);
}

class QOmdb : public QNetworkAccessManager
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(Plot)
    Q_ENUMS(ReturnType)
    Q_PROPERTY(QString id MEMBER m_id USER true)
    Q_PROPERTY(QString title MEMBER m_title USER true)
    Q_PROPERTY(Type type MEMBER m_type USER true)
    Q_PROPERTY(int year MEMBER m_year USER true)
    Q_PROPERTY(Plot plot MEMBER m_plot USER true)
    Q_PROPERTY(ReturnType returnType MEMBER m_returnType USER true)
    Q_PROPERTY(bool includeTomatoRatings MEMBER m_includeTomatoRatings USER true)
public:
    QOmdb(QObject *parent = 0);
    ~QOmdb();
    void fetch();
    void search();

    enum class Type {
        Movie,
        Series,
        Episode
    };

    enum class Plot {
        Short,
        Full
    };

    enum class ReturnType {
        Json,
        Xml
    };

protected:
    void setKeyMaps();
    void _get();
    void append(QString key, QString data);
    void createUrl(bool isSearchMode = false);
    QString getParamKey(QString key);
    QMetaEnum toString(QString element);

protected slots:
    void onFinished(QNetworkReply *reply);

signals:
    void finished(const QByteArray doc, bool isJson = true);

private:
    QString m_baseUrl;
    QString m_id;
    QString m_title;
    Type m_type = Type::Movie;
    int m_year = 0;
    Plot m_plot = Plot::Short;
    ReturnType m_returnType = ReturnType::Json;
    bool m_includeTomatoRatings = false;
    QMap<QString, QString> keyMap;
};

#endif // QOMDB_H
