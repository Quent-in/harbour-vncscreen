/*
VNC Screen: Remote Desktop application for Sailfish OS based on VNC standard.

Copyright (c) 2016 Marcello Di Guglielmo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef INTERFACERFB_H
#define INTERFACERFB_H

#include <QObject>
#include <QImage>
#include <QString>
#include <QTimer>
#include <QtCore>
#include <QKeySequence>
#include  "vncclientthread.h"
#include "screenprovider.h"
#include "sym2rfbkey.h"
class InterfaceRFB : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_PROPERTY(QImage screen READ screen NOTIFY screenChanged)
//    Q_PROPERTY(QString testo READ testo NOTIFY testoChanged)
    Q_PROPERTY(QString vncpath READ vncpath WRITE setVncpath NOTIFY vncpathChanged)
    Q_PROPERTY(QString vncpassword READ vncpassword WRITE setVncpassword NOTIFY vncpasswordChanged)
//    Q_PROPERTY(QString percorso READ percorso NOTIFY percorsoChanged)

public:
    explicit InterfaceRFB(QObject *parent = 0);
    QImage screen();
    QString testo();
    void setVncpath(QString path);
    QString vncpath();
    void setVncpassword(QString password);
    QString vncpassword();
    enum Status
    {
        Connected=1,
        Disconnected=2
    };
private:
    QImage rfbImage;
    QString rfbTesto;
    QTimer *timer;
    VncClientThread *vncThread;
    QUrl urlPath;
    QString urlPassword;
    long vncIndex;
    QList<int> keyEventAccepted;

signals:
    void screenChanged();
//    void testoChanged();
    void vncpathChanged();
    void passwordRequest();
    void vncpasswordChanged();
    void vncStatus(int status);
    void vncImageUpdate(long index);
public slots:
    void vncDisconnect();
    void timerTimeout();
//    void vncMousePositionChanged(int x,int y,int button);
//    void vncMousePressed(int x,int y,int button);
//    void vncMouseReleased(int x,int y,int button);
    void vncMouseEvent(int x,int y,int button);
    void vncKeyEvent(int key,int modifiers, bool pressed);
    void vncKey(QString key);


private slots:
    void onConnected();
    void onDisconnected();
    void onImageUpdate(int x, int y, int w, int h);
};

#endif // INTERFACERFB_H
