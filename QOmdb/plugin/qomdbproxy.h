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

#ifndef QOMDBPROXY_H
#define QOMDBPROXY_H

#include <QObject>
#include <QVariant>
#include "../omdb/qomdb.h"

class QOmdbProxy : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(Plot)
    Q_ENUMS(ReturnType)
    Q_PROPERTY(QString imdb_id MEMBER m_imdb_id WRITE setImdbId)
    Q_PROPERTY(QString title MEMBER m_title WRITE setTitle)
    Q_PROPERTY(Type type MEMBER m_type WRITE setType)
    Q_PROPERTY(int year MEMBER m_year WRITE setYear)
    Q_PROPERTY(Plot plot MEMBER m_plot WRITE setPlot)
    Q_PROPERTY(ReturnType returnType MEMBER m_returnType WRITE setReturnType)
    Q_PROPERTY(bool includeTomatoRatings MEMBER m_includeTomatoRatings WRITE setIncludeTomatoRatings)



public:
    explicit QOmdbProxy(QObject *parent = 0);
    ~QOmdbProxy();

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

signals:
    void finished(const QByteArray doc, bool isJson = true);

public slots:
    void fetch();
    void search();

protected slots:
    void setImdbId(QString arg);
    void setTitle(QString arg);
    void setType(Type arg);
    void setYear(int arg);
    void setPlot(Plot arg);
    void setReturnType(ReturnType arg);
    void setIncludeTomatoRatings(bool arg);

private:
    QString m_imdb_id;
    QString m_title;
    Type m_type = Type::Movie;
    int m_year = 0;
    Plot m_plot = Plot::Short;
    ReturnType m_returnType = ReturnType::Json;
    bool m_includeTomatoRatings = false;
    QOmdb *m_omdb;
};

Q_DECLARE_METATYPE(QOmdbProxy::Type)
Q_DECLARE_METATYPE(QOmdbProxy::Plot)
Q_DECLARE_METATYPE(QOmdbProxy::ReturnType)

#endif // QOMDBPROXY_H
