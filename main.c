#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

static int *vertexList;
static int vertexListSize=0;
static int *vertexNormals;
static int vertexNormalsSize=0;
static int *faces;
static int facesSize=0;

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

    char * fileExt = ".h";

    outputFilename = strtok(argv[1],".");
    char * modelName = malloc(strlen(outputFilename)+ strlen(fileExt)+1);;
    strcpy(modelName,outputFilename);
    printf("%s\n",outputFilename );
    char * temp = malloc(strlen(outputFilename)+ strlen(fileExt)+1); // add 1 for null terminator
    strcpy(temp,outputFilename);
    strcat(temp,fileExt);
    free(outputFilename);
    outputFilename = temp;
    printf("outputFilename: %s\n",outputFilename );

	char objtoken[30];
	char f1[8];
	char f2[8];
	char f3[8];

	float x,y,z; // vertex coordinates
	int v1[2],v2[2],v3[2]; // triangle vertices and normal vectors
	while (fscanf(inputOBJFilePointer, "%s", objtoken) != EOF) {
		if(strcmp(objtoken,"v") == 0 ) { // 0 means a match for vertices
			fscanf(inputOBJFilePointer, "%f %f %f",&x,&y,&z);
			//printf("VERTICES! %.2f %.2f %.2f\n",x,y,z);
			if(vertexList == NULL) { // initialize and add first vertices
				vertexList = (int*)malloc(3 * sizeof(int));
				vertexList[0] = (int)(x * 100.0);
				vertexList[1] = (int)(y * 100.0);
				vertexList[2] = (int)(z * 100.0);
				vertexListSize = 3;
			} else {
				int *temp = (int*)malloc((vertexListSize + 3) * sizeof(int));
                for (int vertex = 0; vertex < vertexListSize; vertex++) {
                    temp[vertex] = vertexList[vertex];
                }
				free(vertexList);
				vertexList = temp;
				vertexList[vertexListSize]   =  (int)(x * 100.0);
				vertexList[vertexListSize+1] =  (int)(y * 100.0);
				vertexList[vertexListSize+2] =  (int)(z * 100.0);
				vertexListSize += 3;
			}
		}
		if(strcmp(objtoken,"vn") == 0 ) { // 0 means a match for vertex normals
            fscanf(inputOBJFilePointer, "%f %f %f",&x,&y,&z);
            //printf("VERTEX NORMALS! %.2f %.2f %.2f\n",x,y,z);
            if(vertexNormals == NULL) { // initialize and add first vertices
                vertexNormals = (int*)malloc(3 * sizeof(int));
                vertexNormals[0] = (int)(x * 100.0);
                vertexNormals[1] = (int)(y * 100.0);
                vertexNormals[2] = (int)(z * 100.0);
                vertexNormalsSize = 3;
            } else {
                int *temp = (int*)malloc((vertexNormalsSize + 3) * sizeof(int));
                for (int vertex = 0; vertex < vertexNormalsSize; vertex++) {
                    temp[vertex] = vertexNormals[vertex];
                }
                free(vertexNormals);
                vertexNormals = temp;
                vertexNormals[vertexNormalsSize]   =  (int)(x * 100.0);
                vertexNormals[vertexNormalsSize+1] =  (int)(y * 100.0);
                vertexNormals[vertexNormalsSize+2] =  (int)(z * 100.0);
                vertexNormalsSize += 3;
            }
		}
		if(strcmp(objtoken,"f") == 0 ) { // 0 means a match for faces
            char * tempface;
			fscanf(inputOBJFilePointer, "%s",f1);
            tempface = strtok(f1,"/");
            v1[0] = atoi(tempface)-1;
            tempface = strtok(NULL,"/");
            v1[1] = atoi(tempface)-1;
            fscanf(inputOBJFilePointer, "%s",f2);
            tempface = strtok(f2,"/");
            v2[0] = atoi(tempface)-1;
            tempface = strtok(NULL,"/");
            v2[1] = atoi(tempface)-1;
            fscanf(inputOBJFilePointer, "%s",f3);
            tempface = strtok(f3,"/");
            v3[0] = atoi(tempface)-1;
            tempface = strtok(NULL,"/");
            v3[1] = atoi(tempface)-1;
			//printf("FACE V: %d %d %d VN: %d %d %d\n", v1[0],v2[0],v3[0], v1[1],v2[1],v3[1]);
            if(faces == NULL) {
                faces = (int*)malloc(6 * sizeof(int));
            } else {
                int *temp = (int*)malloc((facesSize + 6) * sizeof(int));
                for (int faceElement = 0; faceElement < facesSize; faceElement++) {
                    temp[faceElement] = faces[faceElement];
                }
                free(faces);
                faces = temp;
            }
            faces[facesSize]   = v1[0];
            faces[facesSize+1] = v1[1];
            faces[facesSize+2] = v2[0];
            faces[facesSize+3] = v2[1];
            faces[facesSize+4] = v3[0];
            faces[facesSize+5] = v3[1];
            facesSize+=6;
		}
	}

    printf("vertexListSize %d\n",vertexListSize);
    printf("vertexNormalsSize %d\n",vertexNormalsSize);
    printf("facesSize %d\n",facesSize);

	for (int vertex = 0; vertex < vertexListSize/3; vertex++) {
		printf("V[%d]\t x:%d y:%d z:%d size:%d\n",vertex,vertexList[(vertex * 3)],vertexList[(vertex * 3)+1],vertexList[(vertex * 3)+2],vertexListSize);
	}
    for (int vertex = 0; vertex < vertexNormalsSize/3; vertex++) {
        printf("VN[%d]\t x:%d y:%d z:%d size:%d\n",vertex,vertexNormals[(vertex * 3)],vertexNormals[(vertex * 3)+1],vertexNormals[(vertex * 3)+2], vertexNormalsSize);
    }
    for (int face = 0; face < facesSize/6; face++) {
        printf("FACE[%2d]\t V1 %d N1 %d V2 %d N2 %d V3 %d N3 %d size:%d\n",face,faces[(face * 6)],faces[(face * 6)+1],faces[(face * 6)+2],faces[(face * 6)+3],faces[(face * 6)+4],faces[(face * 6)+5], facesSize);
    }

    outputHeaderFilePointer = fopen(outputFilename, "w");

	if (outputHeaderFilePointer == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n",
	          outputFilename);
	  exit(1);
	}



    fprintf(outputHeaderFilePointer, "%sVertices[][] = {",modelName);
    for(int vertex = 0; vertex < vertexListSize/3; vertex++){
        fprintf(outputHeaderFilePointer, "{");
        fprintf(outputHeaderFilePointer, "%d, ", vertexList[(vertex*3)]);
        fprintf(outputHeaderFilePointer, "%d, ", vertexList[(vertex*3)+1]);
        fprintf(outputHeaderFilePointer, "%d",   vertexList[(vertex*3)+2]);
        fprintf(outputHeaderFilePointer, "}");
        if(vertex != (vertexListSize/3) - 1) {
            fprintf(outputHeaderFilePointer, ",\n" );
        }
    }
    fprintf(outputHeaderFilePointer, "};\n");
    fprintf(outputHeaderFilePointer, "%sNormalVectors[][] = {",modelName);
    for(int normalv = 0; normalv < vertexNormalsSize/3; normalv++){
        fprintf(outputHeaderFilePointer, "{");
        fprintf(outputHeaderFilePointer, "%d, ", vertexNormals[(normalv*3)]);
        fprintf(outputHeaderFilePointer, "%d, ", vertexNormals[(normalv*3)+1]);
        fprintf(outputHeaderFilePointer, "%d",   vertexNormals[(normalv*3)+2]);
        fprintf(outputHeaderFilePointer, "}");
        if(normalv != (vertexNormalsSize/3) - 1) {
            fprintf(outputHeaderFilePointer, ",\n" );
        }
    }
    fprintf(outputHeaderFilePointer, "};\n");

    fprintf(outputHeaderFilePointer, "%sFaces[][] = {",modelName);
    for (int face = 0; face < facesSize/6; face++) {
        fprintf(outputHeaderFilePointer, "{");
        fprintf(outputHeaderFilePointer, "%d, ", faces[(face*6)]);
        fprintf(outputHeaderFilePointer, "%d, ", faces[(face*6)+2]);
        fprintf(outputHeaderFilePointer, "%d",   faces[(face*6)+4]);
        fprintf(outputHeaderFilePointer, "}");
        if(face != (facesSize/6) - 1) {
            fprintf(outputHeaderFilePointer, ",\n" );
        }
    }
    fprintf(outputHeaderFilePointer, "};\n");

    fprintf(outputHeaderFilePointer, "%sFaceNormals[] = { ",modelName);
    for (int face = 0; face < facesSize/6; face++) {
        //fprintf(outputHeaderFilePointer, "{");
        fprintf(outputHeaderFilePointer, "%d", faces[(face*6)+1]);
        //fprintf(outputHeaderFilePointer, "%d, ", faces[(face*6)+3]);
        //fprintf(outputHeaderFilePointer, "%d",   faces[(face*6)+5]);
        //fprintf(outputHeaderFilePointer, "}");
        if(face != (facesSize/6) - 1) {
            fprintf(outputHeaderFilePointer, ", " );
        }
    }
    fprintf(outputHeaderFilePointer, "};\n");

    fclose(outputHeaderFilePointer);

}
