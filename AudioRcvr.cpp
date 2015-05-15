#include AudioSubscriber.h

AudioRcvr::update(char* buffer, int bufferSize)
{
	aiPlayback = new AudioInterface(argv[1], SAMPLING_RATE, NUMBER_OF_CHANNELS, SND_PCM_STREAM_PLAYBACK);
	aiPlayback->open();
	aiPlayback->write(buffer);
}