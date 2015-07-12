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

#include "qomdbproxy.h"

QOmdbProxy::QOmdbProxy(QObject *parent)
    : QObject(parent)
{
    m_omdb = new QOmdb(this);
    connect(m_omdb, &QOmdb::finished, this, &QOmdbProxy::finished);
}

QOmdbProxy::~QOmdbProxy()
{
    delete m_omdb;
}

void QOmdbProxy::fetch()
{
    m_omdb->fetch();
}

void QOmdbProxy::search()
{
    m_omdb->search();
}

void QOmdbProxy::setImdbId(QString arg)
{
    m_imdb_id = arg;
    m_omdb->setProperty("id",QVariant::fromValue(m_imdb_id));
}

void QOmdbProxy::setTitle(QString arg)
{
    m_title = arg;
    m_omdb->setProperty("title",QVariant::fromValue(m_title));
}

void QOmdbProxy::setType(Type arg)
{
    m_type = arg;
    m_omdb->setProperty("type",QVariant::fromValue(m_type));
}

void QOmdbProxy::setYear(int arg)
{
    m_year = arg;
    m_omdb->setProperty("year",QVariant::fromValue(m_year));
}

void QOmdbProxy::setPlot(Plot arg)
{
    m_plot = arg;
    m_omdb->setProperty("plot",QVariant::fromValue(m_plot));
}

void QOmdbProxy::setReturnType(ReturnType arg)
{
    m_returnType = arg;
    m_omdb->setProperty("returnType",QVariant::fromValue(m_returnType));
}

void QOmdbProxy::setIncludeTomatoRatings(bool arg)
{
    m_includeTomatoRatings = arg;
    m_omdb->setProperty("includeTomatoRatings",QVariant::fromValue(m_includeTomatoRatings));
}

