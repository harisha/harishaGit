#include <QtGui> 
#include "myVlcPlayer.h"
 
myVlcPlayer::myVlcPlayer(QWidget *parent)
{
    setupUi(this);
    // signals/slots mechanism in action
    connect(btnStart, SIGNAL(clicked()), this, SLOT(startAudio()) ); 
    //connect( btnStop, SIGNAL(clicked()), this, SLOT(stopAudio()) ); 
}

void myVlcPlayer::startAudio()
{
    isPlaying = 1;
    inst = libvlc_new (0, NULL);
    m = libvlc_media_new_path (inst, "/home/harisha/Harisha_samples/vlc_samples/Videos/Waka.mp4");
    mp = libvlc_media_player_new_from_media (m);
    libvlc_media_player_play (mp);
}
         
void myVlcPlayer::stopAudio()
{
           if(isPlaying)
           {
               libvlc_media_player_stop (mp);
           }
}

void myVlcPlayer::changeVol(int level)
{
    libvlc_audio_set_volume(mp,level);
}


