#include "AudioInterface.h"

#define SAMPLING_RATE (22500)
#define NUMBER_OF_CHANNELS (2)
#define BYTES_PER_SAMPLE (2)

int main(int argc, char* argv[])
{
	AudioInterface *aiRecord;
	AudioInterface *aiPlayback;
	
	int rc;
	char *buffer;
	int bufferSize;
	
	if (argc != 2) {
		printf("Usage: %s <playback device (i.e. plughw:1)>",
				argv[0]);
		exit(0);
	}
	
	
	aiRecord = new AudioInterface(argv[1], SAMPLING_RATE, NUMBER_OF_CHANNELS, SND_PCM_STREAM_CAPTURE);
	aiRecord->open();
	bufferSize = aiRecord->getRequiredBufferSize();
	
	buffer  = (char*)malloc(bufferSize);
	
	
	aiPlayback = new AudioInterface(argv[1], SAMPLING_RATE, NUMBER_OF_CHANNELS, SND_PCM_STREAM_PLAYBACK);
	aiPlayback->open();
	
	//bufferSize = aiPlayback->getRequiredBufferSize; //not needed?
	
	do{
		
		memset(buffer, 0, bufferSize);
		
		aiRecord->read(buffer);
		
		//write to the headphones
		aiPlayback->write(buffer, bufferSize);
		
		//bytesToCapture-=bufferSize; //could get rid of.
	}while (true);
	
	aiPlayback->close();
	aiRecord->close();
	
	return 0;
}