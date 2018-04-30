using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
//#include <sys/mman.h>
#include <fcntl.h>
//#include <unistd.h>
#include "imdb.h"
#include <stdlib.h>

const char *const imdb::kActorFileName = "actordata";
const char *const imdb::kMovieFileName = "moviedata";

imdb::imdb(const string& directory)
{
  const string actorFileName = directory + "//" + kActorFileName;
  const string movieFileName = directory + "//" + kMovieFileName;
  
  actorFile = acquireFileMap(actorFileName, actorInfo);
  movieFile = acquireFileMap(movieFileName, movieInfo);
}

bool imdb::good() const
{
  return !( (actorInfo.fd == -1) || 
	    (movieInfo.fd == -1) ); 
}

// you should be implementing these two methods right here... 
bool imdb::getFilm(size_t idx, vector<string>& players ) const {
  
   size_t n = (size_t)*(int*)movieFile;
   cout << "movie =" << n << endl;
   void *film_adr = 0;
   film_adr = (void *)((int *)movieFile + 1 + idx);
   char * base = (char *)((char *)movieFile + *(int *)film_adr);
   
   int name_len = strlen((char *)base);
   char *p = base + name_len + 1;
   
   if(name_len %2 == 0){
    p += 1;
    name_len += 2;
   }
   else{
    name_len++;
   }
   cout<<base<<endl;
   
   unsigned short actor_num = *(unsigned short *)p;
   cout << "actor =" << actor_num << endl;
   size_t current_size = p - base + 2;
   size_t zero_padding = current_size % 4;
   p += zero_padding + 2;
   
   for(int i = 0; i < actor_num ; i++){
   
   unsigned int actor_offset = *(unsigned int *)p;
   p += 4;
   char * actorbase = (char *)((char *)actorFile + actor_offset);
   printf("Actor name : %s\n", actorbase);
   }
   
}
bool imdb::getPlayer(size_t idx, vector<film>& films) const {

        
        size_t n = (size_t)*(int*)actorFile;
        cout <<"player ="<< n << endl;
        void *actor_adr = 0;
        actor_adr = (void *)((int *)actorFile + 1 + idx);
        char * base = (char *)((char *)actorFile + *(int *)actor_adr);
        
        int name_len = strlen((char *)base);
        char *p = base + name_len + 1;
        
        if(name_len %2 == 0){
            p += 1;
            name_len += 2;
        }
        else{
            name_len++;
        }
        cout<<base<<endl;

        unsigned short film_num = *(unsigned short *)p;
        cout<<"film ="<< film_num<<endl;
        size_t current_size = p - base + 2;
        size_t zero_padding = current_size % 4;
        p += zero_padding + 2;
        
    for (int i = 0; i < film_num ; i++){
        
        unsigned int film_offset = *(unsigned int *)p;
        p += 4;
        char * filmbase = (char *)((char *)movieFile + film_offset);
        printf("Film name : %s\n", filmbase);
        
        
    }
    
}

imdb::~imdb()
{
  releaseFileMap(actorInfo);
  releaseFileMap(movieInfo);
}




const void *imdb::acquireFileMap(const string& fileName, struct fileInfo& info)
{
	struct stat stats;
	stat(fileName.c_str(), &stats);

	info.fileSize = stats.st_size;
    
    FILE *fp= fopen(fileName.c_str(), "rb");
    
  
    
	info.fd = (long)fp;
	info.fileMap = (void *)malloc(info.fileSize);

	int ss = 0;
	if (!fp) {
        printf("error: could not open image file : %s\n", fileName.c_str());
	}
	ss = fread((void *)info.fileMap, 1, stats.st_size, fp);


	fclose((FILE *)info.fd);

	return info.fileMap;

		//mmap(0, info.fileSize, PROT_READ, MAP_SHARED, info.fd, 0);
}

void imdb::releaseFileMap(struct fileInfo& info)
{
	if (info.fileMap != NULL)
		free((char * )info.fileMap);

}
