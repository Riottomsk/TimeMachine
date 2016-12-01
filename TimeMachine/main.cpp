#include "streamcontroller.h"
#include "playercontroller.h"
#include "player.h"
#include "insert.h"
#include "select.h"
#include "slicer.h"
#include <iostream>
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{


    {
        /*
        Slicer slicer;
        const char* input ="rtsp://ewns-hls-b-stream.hexaglobe.net/rtpeuronewslive/en_vidan750_rtp.sdp";
        int numberOfSlices = 3;
        slicer.makeMultipleSlices(input, numberOfSlices);
        /*
        {
            QDateTime DateTime(QDate(2002,01,01),QTime(00,00,01));
            quint32 time = DateTime.toTime_t();
            QString iFileName = output;
            //QString iFilePath = QFileInfo("slice_0-5.ts").dir();
            QString iSourceName = "CAM01";
            QString iSourceAdress = "1.1.1.1";
            quint32 iDuration = 333333;
            for(int i = 0; i < stop; ++i)
            {
                iOffset++;
                Insert::insert(++time,iFileName,iSourceName,iSourceAdress,"home/",iDuration);
            }
        }
        */
    }
    //Тест ввода-вывода и бд
    {
        QDateTime InsertDateTime(QDate(2000,01,01),QTime(00,00,00));
        {
            qint32 time1 = InsertDateTime.toTime_t();
            QString iFileName = "slice_0-5.ts";
            QString iFilePath = QFileInfo("slice_0-5.ts").dir().path();
            QString iSourceName = "CAM_01";
            QString iSourceAdress = "1.1.1.1";
            quint32 iDuration = 600000;
            Insert::insert(time1,iFileName,iSourceName,iSourceAdress,iFilePath,iDuration);
        }
        {
            qint32 time2 = InsertDateTime.addMSecs(600000).toTime_t();
            QString iFileName = "slice_5-10.ts";
            QString iFilePath = QFileInfo("slice_5-10.ts").dir().path();
            QString iSourceName = "CAM_01";
            QString iSourceAdress = "1.1.1.1";
            quint32 iDuration = 600000;
            Insert::insert(time2,iFileName,iSourceName,iSourceAdress,iFilePath,iDuration);
        }
        {
        QDateTime SelectDateTime(QDate(2000,01,01),QTime(00,05,00));
        qint32 time = SelectDateTime.toTime_t();
        std::cout << "DateTime:"     << Select::selectPreviousDateTime(time)
                  << " Duration:"    << Select::selectDuration(time)
                  << " Path:"        << Select::selectPath(time).toStdString()
                  << " SourceAdress:"<< Select::selectSourceAdress(time).toStdString()
                  << " SourceName:"  << Select::selectSourceName(time).toStdString()
                  << " File:"        << Select::selectFile(time).toStdString()
                  << " Offset:"      << Select::selectOffset(time)
                  << " PercenOffset:"<< Select::selectPercentOffset(time)
                  << " NextFile:"    << Select::selectNextFile(Select::selectFile(time)).toStdString()
                                     << std::endl;
        }
    }
    QApplication a(argc, argv);
    Player player;
    PlayerController *playerController = new PlayerController(&player);
    StreamController *streamController = new StreamController();
    player.show();

        //Сигналы от PlayerController к StreamController
        QObject::connect(playerController, &PlayerController::requestToObtainSource,
                        streamController, &StreamController::requestedToObtainSource);
        QObject::connect(playerController, &PlayerController::requestToStream,
                        streamController, &StreamController::requestedToStream);
        QObject::connect(playerController, &PlayerController::requestToPauseStream,
                        streamController, &StreamController::requestedToPauseStream);

        //Сигналы от StreamController к PlayerController
        QObject::connect(streamController, &StreamController::signalSourceObtained,
                        playerController, &PlayerController::handleSourceObtained);
        QObject::connect(streamController, &StreamController::signalStreamStarted,
                        playerController, &PlayerController::attemptToPlayStream);



    return a.exec();
}
