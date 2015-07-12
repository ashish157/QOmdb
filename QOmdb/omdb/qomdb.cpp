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

#include "qomdb.h"

QOmdb::QOmdb(QObject *parent)
    : QNetworkAccessManager(parent)
{
    setKeyMaps();
    m_baseUrl = "http://www.omdbapi.com/?";
    connect(this, &QNetworkAccessManager::finished, this, &QOmdb::onFinished);
}

QOmdb::~QOmdb()
{

}

void QOmdb::setKeyMaps()
{
    keyMap["id"] = "i";
    keyMap["title"] = "t";
    keyMap["year"] = "y";
    keyMap["plot"] = "plot";
    keyMap["type"] = "type";
    keyMap["returnType"] = "r";
    keyMap["includeTomatoRatings"] = "tomatoes";
    keyMap["search"] = "s";
}

void QOmdb::fetch()
{
    createUrl(false);
    _get();
}

void QOmdb::search()
{
    createUrl(true);
    _get();
}

void QOmdb::_get()
{
    if(m_title.isEmpty() && m_id == 0) {
        QString err = "{ \"Error\": \"Title or IMDb id required\"}";
        emit finished(err.toLatin1());
        return;
    }
    m_baseUrl.chop(1);
    QNetworkRequest request;
    request.setUrl(QUrl(m_baseUrl));
    get(request);
}

void QOmdb::onFinished(QNetworkReply *reply)
{
    emit finished(reply->readAll(),m_returnType==ReturnType::Json?true:false);
}

QString QOmdb::getParamKey(QString key)
{
    return keyMap.value(key);
}

void QOmdb::append(QString key, QString data)
{
    m_baseUrl.append(getParamKey(key));
    m_baseUrl.append("=");
    m_baseUrl.append(data);
    m_baseUrl.append("&");
}

void QOmdb::createUrl(bool isSearchMode)
{
    const auto *metaobject = metaObject();
    int count = metaobject->propertyCount();
    for (int i=0; i<count; ++i) {
        auto metaproperty = metaobject->property(i);
        if(metaproperty.isUser()) {
            const char *name = metaproperty.name();
            auto value = property(name);
            if(metaproperty.isEnumType()) {
                auto metaEnum = toString(metaproperty.typeName());
                QString t = metaEnum.valueToKey(value.toInt());
                append(name,t);
            } else {
                QString t = value.toString();
                if(QString::fromLatin1(value.typeName())=="QString") {
                    if(isSearchMode) name = "search";
                    if(!t.isEmpty())
                        append(name,t);
                } else if(QString::fromLatin1(value.typeName())=="int") {
                    if(t!="0")
                        append(name,t);
                }
                else
                    append(name,QString(value.toBool()?"true":"false"));
            }
        }
    }
}

QMetaEnum QOmdb::toString(QString element)
{
    int index = metaObject()->indexOfEnumerator(element.toUtf8().constData());
    return metaObject()->enumerator(index);
}
