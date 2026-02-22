#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct coordinate
{
    int x;
    int y;
};

void open_file() {
    FILE *file = fopen("veri.txt", "r");

    if (file) {
            int character;

        while ((character = fgetc(file)) != EOF) {
            putchar(character);
        }

        fclose(file);
    } else {
        printf("Dosya acilamadi!\n");
    }
}

char *get_line(int whichLine) {
    FILE *file = fopen("veri.txt", "r");

    int character;
    int lineNumber = 1;

    char *line;
    int lineLength = 0;

    line = (char *)malloc(1);

    if (file) {
        while ((character = fgetc(file)) != EOF) {
            if (character == '\n') {
                lineNumber++;   
            } else {
                if (lineNumber == whichLine)
                {
                    line = (char *) realloc(line, lineLength + 2);
                    line[lineLength] = (char)character;
                    line[lineLength + 1] = '\0';


                    lineLength++;
                }
            }
        }

        fclose(file);
    } else {
        printf("Dosya acilamadi!\n");
    }

    return line;
}

  void draw_background(){
    initwindow(1000, 750);

    int size = 10;

	setcolor(LIGHTGRAY);

    for (int x = 0; x < getmaxx(); x += size) {
        for (int y = 0; y < getmaxy(); y += size) {
            rectangle(x, y, x + size, y + size);
        }
    } 
}

   void draw_final(int area[100][100], int row, int column) {
    initwindow(1000, 750);
 	   
   	int size = 10;
   	
	for (int i = 0; i < row; i++) {
	    for (int j = 0; j < column; j++) {
            int x = j * size;
            int y = i * size;
            
            if (area[i][j] == 0) {
            	setcolor(LIGHTGRAY);
    			rectangle(x, y, x + size, y + size);
            } 
            else if (area[i][j] == 1) {
            	setfillstyle(SOLID_FILL, MAGENTA);
    			bar(x, y, x + size, y + size);
            }
            else if (area[i][j] == 2) {
            	setfillstyle(SOLID_FILL, BLUE);
    			bar(x, y, x + size, y + size);
            }
            else if (area[i][j] == 4) {
            	setfillstyle(SOLID_FILL, GREEN);
    			bar(x, y, x + size, y + size);
            }
            else if (area[i][j] == 8) {
            	setfillstyle(SOLID_FILL, CYAN);
    			bar(x, y, x + size, y + size);
            }
            else if (area[i][j] == 16) {
            	setfillstyle(SOLID_FILL, YELLOW);
    			bar(x, y, x + size, y + size);
            }
		}
	}
	
}

void findMinMax(struct coordinate coordinates[], struct coordinate *start, struct coordinate *end, int len) {

    int minX = coordinates[0].x;
    int minY = coordinates[0].y;
    int maxX = coordinates[0].x;
    int maxY = coordinates[0].y;

    for (int i = 1; i < len; i++) {
        if (coordinates[i].x < minX) {
            minX = coordinates[i].x;
        }
        if (coordinates[i].x > maxX) {
            maxX = coordinates[i].x;
        }
        if (coordinates[i].y < minY) {
            minY = coordinates[i].y;
        }
        if (coordinates[i].y > maxY) {
            maxY = coordinates[i].y;
        }
    }

    start->x = minX;
    start->y = minY;
    end->x = maxX;
    end->y = maxY;
}

float max (float num1, float num2) {
    if (num1 > num2) {
        return num1;
    } else {
        return num2;
    }
}

int main() {
   	int whichLine;
   	int birimSondaj;
   	int birimPlatform;

    system("curl http://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt -o veri.txt");
	printf("\n\n");
    
	open_file();

    printf("\n\nKacinci satir hesaplansin: ");
    scanf("%d", &whichLine);
    
	do {
    	printf("Birim sondaj maliyeti giriniz (1 - 10): ");
    	scanf("%d", &birimSondaj);
    	
    	if (birimSondaj < 1 || birimSondaj > 10) {
    		printf("1 ile 10 arasi bir deger giriniz!\n");
		} else {
			break;
		}
	} while(1);
	
	do {
    	printf("Birim platform maliyeti giriniz: ");
    	scanf("%d", &birimPlatform);
    	
    	if (birimPlatform < 0) {
    		printf("Maliyet negatif olamaz!\n");
		} else {
			break;
		}
	} while(1);
    

    char *line = get_line(whichLine);

    struct coordinate coordinates[3][30]; 
    int coordinateLenghts[3];
    int count = 0; 
    int placament = 0;
    int x, y;
   
   // Koordinatlarý structlara kaydedildi ve þekil sayýsý kontrol edildi
    while (*line) {
        if (*line == '(') {
            sscanf(line, "(%d,%d)", &x, &y); 

            coordinates[placament][count].x = x;
            coordinates[placament][count].y = y;
            count++;  

            if (placament == 3 && count >= 1) {
                printf("En fazla 3 sekil girilebilir!!");
                exit(1);
            }

            if (count > 1) {
                if(x == coordinates[placament][0].x && y == coordinates[placament][0].y) {
                    coordinateLenghts[placament] = count;
                    placament++;
                    count = 0;
                }
            }
        }
        line++;
    }
	
	//ilk background çizildi üstüne þekiller çizildi	
	draw_background();
	setcolor(WHITE);
			
	for(int i = 0; i < placament; i++) {
		int drawShape[coordinateLenghts[i] * 2];
		
		for(int a = 0; a < coordinateLenghts[i] * 2; a += 2) {
			drawShape[a] = coordinates[i][a / 2].x * 10;
			drawShape[a + 1] = coordinates[i][a / 2].y * 10;
		}
				
		drawpoly(coordinateLenghts[i], drawShape);
	}

    getch();
    closegraph();
	
    // Sekiller 1 ile cizildi	
	int area[100][100] = {{0}};
	int shapeArea[placament] = {0};

	for (int order = 0; order < placament; order++) {
	 
    int firstLine = 0;

    // asagýdaki 3 yazan yeri kullanacagin koordinatýn eleman sayýsýnýn 1 eksigi yaz coordinates[4] için 3 mesela
    for (int i = 0; i < coordinateLenghts[order] - 1; i++) {
        float wrongSlope = (float) (coordinates[order][i + 1].x - coordinates[order][i].x) / (coordinates[order][i + 1].y - coordinates[order][i].y);
        wrongSlope = fabs(wrongSlope);

        float slope = (float) (coordinates[order][i + 1].y - coordinates[order][i].y) / (coordinates[order][i + 1].x - coordinates[order][i].x);
        slope = fabs(slope);    
        
        int roundedNumber = round(slope);
        int yChange = 0;
        int control = 1;
        int way = 0;   // 1 yatay, 2 dikey
       
        if (coordinates[order][i].y < coordinates[order][i + 1].y && coordinates[order][i].x < coordinates[order][i + 1].x ) {
            for (int j = coordinates[order][i].x; j < coordinates[order][i + 1].x; j++) {
                if (roundedNumber != slope && control) {
                    control = 0;

                    float value = max(slope, wrongSlope);
                    int ceilValue = ceil(value);

                    if (slope < roundedNumber) {
                        for (int x = 0; x < ceilValue; x++) {
                            area[coordinates[order][i].y + firstLine][j + x] = -1;
                        }

                        way = 1;
                        j = j + ceilValue - 1;
                        yChange++;
                    } else {
                        for (int x = 0; x < ceilValue; x++) {
                            area[coordinates[order][i].y + x + firstLine][j] = -1;
                        }

                        way = 2;
                        yChange += ceilValue;
                    }
                } else {
                    if (way == 1) {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y + yChange + firstLine][j + x] = -1;     
                        }

                        yChange++;
                    } else if (way == 2) {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y + yChange + x + firstLine][j] = -1;    
                        }

                        yChange += roundedNumber;
                    } else {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y + yChange + firstLine][j + x] = -1;
                        }
                       
                        yChange ++;
                    }
                }
            }

            firstLine = 1;
        }


        else if (coordinates[order][i].y < coordinates[order][i + 1].y && coordinates[order][i].x > coordinates[order][i + 1].x ) {
            for (int j = coordinates[order][i].x - firstLine; j > coordinates[order][i + 1].x - firstLine; j--) {
                if (roundedNumber != slope && control) {
                    control = 0;

                    float value = max(slope, wrongSlope);
                    int ceilValue = ceil(value);

                    if (slope < roundedNumber) {
                        for (int x = 0; x < ceilValue; x++) {
                            area[coordinates[order][i].y][j - x] = -1;
                        }

                        way = 1;
                        j = j - ceilValue + 1 - firstLine;
                        yChange++;
                    } else {
                        for (int x = 0; x < ceilValue; x++) {
                            area[coordinates[order][i].y - x][j] = -1;
                        }

                        way = 2;
                        yChange += ceilValue;
                    }
                } else {
                    if (way == 1) {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y + yChange][j - x] = -1;   
                        }

                        yChange++;
                    } else if (way == 2) {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y + yChange + x][j] = -1;    
                        }

                        yChange += roundedNumber;
                    } else {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y + yChange + x][j] = -1;
                        }
                       
                        yChange += roundedNumber;
                    }
                }
            }

            firstLine = 1;
        }

        else if (coordinates[order][i].y > coordinates[order][i + 1].y && coordinates[order][i].x > coordinates[order][i + 1].x ) {
            for (int j = coordinates[order][i].x - firstLine; j > coordinates[order][i + 1].x - firstLine; j--) {
                if (roundedNumber != slope && control) {
                    control = 0;

                    float value = max(slope, wrongSlope);
                    int ceilValue = ceil(value);

                    if (slope < roundedNumber) {
                        for (int x = 0; x < ceilValue; x++) {
                            area[coordinates[order][i].y - firstLine][j - x] = -1;
                        }

                        way = 1;
                        j = j - ceilValue + 1 - firstLine;
                        yChange++;
                    } else {
                        for (int x = 0; x < ceilValue; x++) {
                            area[coordinates[order][i].y - x - firstLine][j] = -1;
                        }

                        way = 2;
                        yChange += ceilValue;
                    }
                } else {
                    if (way == 1) {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y - yChange - firstLine][j - x] = -1;
                        }

                        yChange++;
                    } else if (way == 2) {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y - yChange - x - firstLine][j] = -1;
                        }

                        yChange += roundedNumber;
                    } else {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y - yChange - firstLine - x][j] = -1;
                        }

                        yChange += roundedNumber;
                    }
                }
            }

            firstLine = 1;
        }

        else if (coordinates[order][i].y > coordinates[order][i + 1].y && coordinates[order][i].x < coordinates[order][i + 1].x ) {
            for (int j = coordinates[order][i].x; j < coordinates[order][i + 1].x; j++) {
                if (roundedNumber != slope && control) {
                    control = 0;

                    float value = max(slope, wrongSlope);
                    int ceilValue = ceil(value);

                    if (slope < roundedNumber) {
                        for (int x = 0; x < ceilValue; x++) {
                            area[coordinates[order][i].y - firstLine][j + x] = -1;
                        }

                        way = 1;
                        j = j + ceilValue + 1 - firstLine;
                        yChange++;
                    } else {
                        for (int x = 0; x < ceilValue; x++) {
                            area[coordinates[order][i].y - x - firstLine][j] = -1;
                        }

                        way = 2;
                        yChange += ceilValue;
                    }
                } else {
                    if (way == 1) {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y - yChange - firstLine][j + x] = -1;
                        }

                         yChange++;
                    } else if (way == 2) {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y - yChange - x - firstLine][j] = -1;    
                        }

                        yChange += roundedNumber;
                    } else {
                        for (int x = 0; x < roundedNumber; x++) {
                            area[coordinates[order][i].y - yChange - firstLine - x][j] = -1;
                        }

                        yChange += roundedNumber;
                    }
                }
            }

            firstLine = 1;
        }

        else if (coordinates[order][i].y == coordinates[order][i + 1].y && coordinates[order][i].x < coordinates[order][i + 1].x ) {
            for (int j = coordinates[order][i].x + firstLine; j < coordinates[order][i + 1].x; j++) {
                area[coordinates[order][i].y][j] = -1;
            }

            firstLine = 1;
        }

        else if (coordinates[order][i].y == coordinates[order][i + 1].y && coordinates[order][i].x > coordinates[order][i + 1].x) {
            for (int j = coordinates[order][i].x - firstLine; j > coordinates[order][i + 1].x; j--) {
                area[coordinates[order][i].y - firstLine][j] = -1;
            }

            firstLine = 1;
        }

        else if (coordinates[order][i].y < coordinates[order][i + 1].y && coordinates[order][i].x == coordinates[order][i + 1].x) {
            for (int j = coordinates[order][i].y + firstLine; j < coordinates[order][i + 1].y; j++) {
                area[j][coordinates[order][i].x - firstLine] = -1;
            }

            firstLine = 1;
        }

        else if (coordinates[order][i].y > coordinates[order][i + 1].y && coordinates[order][i].x == coordinates[order][i + 1].x) {
            for (int j = coordinates[order][i].y - firstLine; j > coordinates[order][i + 1].y; j--) {
                area[j][coordinates[order][i].x] = -1;
            }

            firstLine = 1;
        }
    }

    for (int i = 0; i < 100; i++) {
	    for (int j = 0; j < 100; j++) {
            if (area[i][j] == -1 && area[i][j - 1] != -1) {
                if (area[i][++j] != -1) {
                    while (area[i][j] != -1)
                    {
                        area[i][j++] = -1;
                    }     
                }
            }
		}
	}
	
	 for (int i = 0; i < 100; i++) {
	    for (int j = 0; j < 100; j++) {
	    	if (area[i][j] == -1) {
	    		shapeArea[order]++;
			}
	    }
	}
}

	//Kare alanlarýnýn degerleri ayarlandi
	for (int i = placament - 1; i > 0; i--) {
		shapeArea[i] -= shapeArea[i - 1]; 
	}
	
	printf("\n");
	
	int kaynakRezervDegeri[placament];
	int totalSum = 0;
	
	//Kare alanlarýnýn degerleri bastirildi
	for ( int i = 0; i < placament; i++) {
	    printf("%d. SEKIL ALANI: %d\n", i + 1, shapeArea[i]);
	    kaynakRezervDegeri[i] = shapeArea[i] * 10;
	    totalSum += shapeArea[i];
	}
	
	//Kareler alanlara bolundu
	int square_sizes[5] = {15, 7, 3, 1, 0};
    int status = 1;
    int sizeToUse = 0;
	int squareCount = 0;
	
    for (int i = 0; i < 100; i++) {
	    for (int j = 0; j < 100; j++) {
            if (area[i][j] == -1) {
            	squareCount++;
            	
                for (int size = 0; size < 5; size++) {
                    status = 1;

                    for (int passed = square_sizes[size]; passed >= 0; passed--) {     
                        if (i + passed < 100 && j + passed < 100) {
                            if ((area[i][j + passed] == 0 || area[i][j + passed] != -1 )||
                                (area[i + passed][j] == 0 || area[i + passed][j] != -1) ||
                                (area[i + passed][j + passed] == 0 || area[i + passed][j + passed] != -1)) {
                                status = 0;
                            }
                        }

                        if (status == 0) {
                            break;
                        }
                    }  

                    if (status)
                    {
                        sizeToUse = square_sizes[size];
                        break;
                    }        
                }

                for (int a = 0; a <= sizeToUse; a++) {
                    for (int b = 0; b <= sizeToUse; b++) {
                        area[i + a][j + b] = sizeToUse + 1;
                    }
                }
            }
        }
	}
	
	int totalReserve = 0;
	
	for (int i = 0; i < placament; i++) {
		totalReserve += kaynakRezervDegeri[i];
	}

	int cost = totalSum * birimSondaj + squareCount * birimPlatform;
	int finalSituation = totalReserve - cost;
	
	//SON DURUM ZARAR ISE BIRIM KARELERIN DISINA CIKILARAK OLABILCEK EN BUYUK KARELERE BOLUNDU	
	if (finalSituation < 0) {
		squareCount = 0;
		totalSum = 0;

		for (int e = 0; e < placament; e++) {
			struct coordinate startCoordinate;
    		struct coordinate endCoordinate;
    
    		//SEKILI KARE ICINE ALMAK ICIN KARENIN SOL UST VE SAG ALT KOORDINATLARI BULUNDU
    		findMinMax(coordinates[e], &startCoordinate, &endCoordinate, coordinateLenghts[e]);

    		int statusS = 1;
    		int sizeToUseS = 0;

    		for (int i = startCoordinate.y; i < endCoordinate.y; i++) {
        		for (int j = startCoordinate.x; j < endCoordinate.x; j++) {
            		area[i][j] = -1;
            		totalSum++;
        		}
    		}

    		for (int i = startCoordinate.y; i < endCoordinate.y; i++) {
	    		for (int j = startCoordinate.x; j < endCoordinate.x; j++) {
            		if (area[i][j] == -1) {
            			squareCount++;
            			
                		for (int size = 0; size < 5; size++) {
                    		statusS = 1;

                    		for (int passed = square_sizes[size]; passed >= 0; passed--) {     
                        		if (i + passed <= endCoordinate.y && j + passed <= endCoordinate.x) {
                            		if ((area[i][j + passed] == 0 || area[i][j + passed] != -1 )||
                                		(area[i + passed][j] == 0 || area[i + passed][j] != -1) ||
                                		(area[i + passed][j + passed] == 0 || area[i + passed][j + passed] != -1)) {
                                		statusS = 0;
                            		}
                        		}

                        		if (statusS == 0) {
                            		break;
                        		}
                    		}  

                    		if (statusS)
                    		{
                        		sizeToUseS = square_sizes[size];
                        		break;
                    		}        
                		}

                		for (int a = 0; a <= sizeToUseS; a++) {
                    		for (int b = 0; b <= sizeToUseS; b++) {
                        		area[i + a][j + b] = sizeToUseS + 1;
                    		}
                		}
            		}
        		}
			}
		}
	}
	
	cost = totalSum * birimSondaj + squareCount * birimPlatform;
	finalSituation = totalReserve - cost;
	
	printf("\nToplam rezerv degeri: %d ", totalReserve);
	printf("\nToplam sondaj alani: %d ", totalSum);
	printf("\nToplam sondaj maliyeti: %d ", totalSum * birimSondaj);
	printf("\nToplam platform sayisi: %d ", squareCount);
	printf("\nToplam platform maliyeti: %d ", squareCount * birimPlatform);

	//Sekillerin en son renkli hali cizdirildi
	draw_final(area, 100, 100);
	
	setcolor(WHITE);
	for(int i = 0; i < placament; i++) {
		int drawShape[coordinateLenghts[i] * 2];
		
		for(int a = 0; a < coordinateLenghts[i] * 2; a += 2) {
			drawShape[a] = coordinates[i][a / 2].x * 10;
			drawShape[a + 1] = coordinates[i][a / 2].y * 10;
		}
				
		drawpoly(coordinateLenghts[i], drawShape);
	}

	 printf("\n\nKar - zarar durumu: %d ", finalSituation);
    
    if (finalSituation < 0) {
    	printf("ZARAR");
	} else if (finalSituation > 0) {
		printf("KAR");
	} else {
		printf("KAR - ZARAR YOK");
	}

	
	getch();
    closegraph();
    
   
        

    return 0;
}
