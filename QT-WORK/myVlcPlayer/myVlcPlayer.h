#ifndef MYVLCPLAYER_H 
#define MYVLCPLAYER_H

#include "ui_myVlcPlayer.h"

#include <stdio.h>
#include <stdlib.h>
#include <vlc/vlc.h>
#include <iostream>

#include <QObject>


class myVlcPlayer : public QWidget, public Ui_myVlcPlayerDlg
{
       Q_OBJECT

       private:
       libvlc_instance_t * inst;
       libvlc_media_player_t *mp;
       libvlc_media_t *m;
       char isPlaying;

       public:
       myVlcPlayer(QWidget *parent = 0); 
        
       public slots:
       void startAudio();
       void stopAudio();
       void changeVol(int level);
}; 

#endif

