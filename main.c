#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

static int *vertexList;
static int vertexListSize;
static int *vertexNormals;
static int vertexNormalsSize;
static int *faces;
static int facesSize;

int main(int argc, char *argv[], char**envp) {

    printf("HELLO WORLD\n");
	for(int i = 0; i < argc;i++){
		printf("%s\n",argv[i]);
	}
	FILE *inputOBJFilePointer, *outputHeaderFilePointer;
	char *mode = "r";
	char *outputFilename;

	inputOBJFilePointer = fopen(argv[1], mode);

	if (inputOBJFilePointer == NULL) {
	  fprintf(stderr, "Can't open input file in.list!\n");
	  exit(1);
	}

	char objtoken[30];
	char f1[8];
	char f2[8];
	char f3[8];

	float x,y,z; // vertex coordinates
	int v1,v2,v3; // triangle vertices
	while (fscanf(inputOBJFilePointer, "%s", objtoken) != EOF) {
		if(strcmp(objtoken,"v") == 0 ) { // 0 means a match
			fscanf(inputOBJFilePointer, "%f %f %f",&x,&y,&z);
			printf("VERTICES! %.2f %.2f %.2f\n",x,y,z);
			if(vertexList == NULL) { // initialize and add first vertices
				printf("first run\n");
				vertexList = (int*)malloc(3 * sizeof(int));
				vertexList[0] = (int)(x * 100.0);
				vertexList[1] = (int)(y * 100.0);
				vertexList[2] = (int)(z * 100.0);
				vertexListSize = 3;
				for (int vertex = 0; vertex < vertexListSize/3; vertex++) {
					printf("Vinit[%d] x:%d y:%d z:%d size:%d\n",vertex,vertexList[(vertex * 3)],vertexList[(vertex * 3)+1],vertexList[(vertex * 3)+2], vertexListSize);
				}
			} else {
				for (int vertex = 0; vertex < vertexListSize/3; vertex++) {
					printf("V[%d] x:%d y:%d z:%d size:%d\n",vertex,vertexList[(vertex * 3)],vertexList[(vertex * 3)+1],vertexList[(vertex * 3)+2], vertexListSize);
				}
				printf("\n");
				int *temp = (int*)malloc((vertexListSize + 3) * sizeof(int));
                for (int vertex = 0; vertex < vertexListSize; vertex++) {
                    temp[vertex] = vertexList[vertex];
                }
				free(vertexList);
				vertexList = temp;
                printf("vertexListSize Index %d %d %d\n", vertexListSize,vertexListSize+1,vertexListSize+2);
				vertexList[vertexListSize]   =  (int)(x * 100.0);
				vertexList[vertexListSize+1] =  (int)(y * 100.0);
				vertexList[vertexListSize+2] =  (int)(z * 100.0);
				vertexListSize += 3;
                printf("END OF VN WHILE LOOP ITERATION SIZE %d\n",vertexNormalsSize );
			}
		}
		if(strcmp(objtoken,"vn") == 0 ) { // 0 means a match
            fscanf(inputOBJFilePointer, "%f %f %f",&x,&y,&z);
            printf("VERTEX NORMALS! %.2f %.2f %.2f\n",x,y,z);
            if(vertexNormals == NULL) { // initialize and add first vertices
                printf("first run\n");
                vertexNormals = (int*)malloc(3 * sizeof(int));
                vertexNormals[0] = (int)(x * 100.0);
                vertexNormals[1] = (int)(y * 100.0);
                vertexNormals[2] = (int)(z * 100.0);
                vertexNormalsSize = 3;
                for (int vertex = 0; vertex < vertexNormalsSize/3; vertex++) {
                    printf("VNinit[%d] x:%d y:%d z:%d size:%d\n",vertex,vertexNormals[(vertex * 3)],vertexNormals[(vertex * 3)+1],vertexNormals[(vertex * 3)+2], vertexListSize);
                }
            } else {
                for (int vertex = 0; vertex < vertexNormalsSize/3; vertex++) {
                    printf("VN[%d] x:%d y:%d z:%d size:%d\n",vertex,vertexNormals[(vertex * 3)],vertexNormals[(vertex * 3)+1],vertexNormals[(vertex * 3)+2], vertexListSize);
                }
                printf("\n");
                int *temp = (int*)malloc((vertexNormalsSize + 3) * sizeof(int));
                for (int vertex = 0; vertex < vertexNormalsSize; vertex++) {
                    temp[vertex] = vertexNormals[vertex];
                }
                free(vertexNormals);
                vertexNormals = temp;
                printf("vertexNormals Index %d %d %d\n", vertexNormalsSize,vertexNormalsSize+1,vertexNormalsSize+2);
                vertexNormals[vertexNormalsSize]   =  (int)(x * 100.0);
                vertexNormals[vertexNormalsSize+1] =  (int)(y * 100.0);
                vertexNormals[vertexNormalsSize+2] =  (int)(z * 100.0);
                vertexNormalsSize += 3;
                printf("END OF VN WHILE LOOP ITERATION SIZE %d\n",vertexNormalsSize );
            }
		}
		if(strcmp(objtoken,"f") == 0 ) { // 0 means a match
			fscanf(inputOBJFilePointer, "%s %s %s",f1,f2,f3);
			printf("FACES! %s %s %s\n", f1,f2,f3);
		}
	}

    printf("vertexListSize %d\n",vertexListSize);
    printf("vertexNormalsSize %d\n",vertexNormalsSize);

	for (int vertex = 0; vertex < vertexListSize/3; vertex++) {
		printf("V[%d] x:%d y:%d z:%d\n",vertex,vertexList[(vertex * 3)],vertexList[(vertex * 3)+1],vertexList[(vertex * 3)+2]);
	}
    for (int vertex = 0; vertex < vertexNormalsSize/3; vertex++) {
        printf("VN[%d] x:%d y:%d z:%d size:%d\n",vertex,vertexNormals[(vertex * 3)],vertexNormals[(vertex * 3)+1],vertexNormals[(vertex * 3)+2], vertexListSize);
    }

	outputHeaderFilePointer = fopen(outputFilename, "w");

	if (outputHeaderFilePointer == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n",
	          outputFilename);
	  exit(1);
	}

}
