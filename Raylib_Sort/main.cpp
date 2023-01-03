//
//  main.cpp
//  Raylib_Sort
//
//  Created by Floris Kruger on 10/20/22.
//

#include "raylib.h"
#include <iostream>
#include <string>

#define ScreenWidth 1200
#define ScreenHeight 700

#define MinWindowWidth 1200
#define MinWindowHeight 700

#define FPS 20

// Number of Bars
#define numOfBars 50

// Array holding Bars
int arr[numOfBars];

// Array holding Bar Heights
double randHeights[numOfBars];

// Array holding Bar Color State
Color BarCol[numOfBars];

// Bools
bool shouldRandBars = true;
bool shouldShowMenu = true;
bool shouldShowOptions = false;
bool shouldStartSorting = false;
bool doneSorting = false;

// Button Bools
bool bubbleSrtPressed = false;
bool selectionSrtPressed = false;
bool insertionSrtPressed = false;
bool quickSrtPressed = false;

void DrawBars(int arr[], double randHeights[], Color color[]){
    
    double barWidth = ((float)GetScreenWidth()/numOfBars);
    
    for (int i=0; i<numOfBars; i++){
        
        int barHeight = GetScreenHeight()-randHeights[i];
        int intBarVal = randHeights[i];
        std::string barVal = std::to_string(intBarVal);
        char val[barVal.size()+1];
        strcpy(val, barVal.c_str());
        
        if (doneSorting == false){
            DrawRectangle(i*barWidth, barHeight, barWidth, randHeights[i], color[i]);
            DrawText(val, i*barWidth, barHeight-10, 8, BLACK);
        }
        else if (doneSorting == true){
            color[i] = GREEN;
            DrawRectangle(i*barWidth, barHeight, barWidth, randHeights[i], color[i]);
            DrawText(val, i*barWidth, barHeight-10, 8, BLACK);
        }
    }
}

void RandomizeBars(double randHeights[]){
    
    for (int i=0; i<numOfBars; i++){
        randHeights[i] = GetRandomValue(5, 550);
    }
    
    shouldRandBars = false;
    return;
}

void Button(float x, float y, char *Text, Color color, bool &state){
    
    float font = 20;
    Rectangle r1 = {
        .x = x,
        .y = y,
        .width = (float) MeasureText(Text, font),
        .height = (float) font,
    };
    
    if (CheckCollisionPointRec(GetMousePosition(), r1)){
        DrawText(Text, x, y, font, BLUE);
        if (IsMouseButtonPressed(0)){
            
            if (state==true){
                state=false;
            }
            else{
                state=true;
            }
            return;
        }
    }
    else{
        DrawText(Text, x, y, font, color);
    }
    
    return;
}

void bubbleSrtBtn(char bubbkeSrtTxt[]){
    Color color;
    if (bubbleSrtPressed){
        insertionSrtPressed = false;
        selectionSrtPressed = false;
        quickSrtPressed = false;
        color = GREEN;
    }
    else{
        color = RED;
    }

    Button((GetScreenWidth()/8)*1, GetScreenHeight()/20, bubbkeSrtTxt, color, bubbleSrtPressed);
}
void selectionSrtBtn(char selectionTxt[]){
    Color color;
    if (selectionSrtPressed){
        bubbleSrtPressed = false;
        insertionSrtPressed = false;
        quickSrtPressed = false;
        color = GREEN;
    }
    else{
        color = RED;
    }
  
    Button((GetScreenWidth()/8)*2, GetScreenHeight()/20, selectionTxt, color, selectionSrtPressed);
}
void insertionSrtBtn(char insertionTxt[]){
    Color color;
    
    if (insertionSrtPressed){
        bubbleSrtPressed = false;
        selectionSrtPressed = false;
        quickSrtPressed = false;
        color = GREEN;
    }
    else{
        color = RED;
    }
  
    Button(((GetScreenWidth()/8)*3)+25, GetScreenHeight()/20, insertionTxt, color, insertionSrtPressed);
}
void quickSrtBtn(char quickTxt[]){
    Color color;
    
    if (quickSrtPressed){
        bubbleSrtPressed = false;
        insertionSrtPressed = false;
        selectionSrtPressed = false;
        color = GREEN;
    }
    else{
        color = RED;
    }
  
    Button(((GetScreenWidth()/8)*4)+50, GetScreenHeight()/20, quickTxt, color, quickSrtPressed);
}
void showMenu(){
    
    char randArrTxt[] = "Randomize Array!";
    Button(((GetScreenWidth()/8)*6)+30, GetScreenHeight()/20, randArrTxt, DARKGRAY, shouldRandBars);

    // Bubble Sort
    char bubbleSrtTxt[] = "Bubble Sort,";
    bubbleSrtBtn(bubbleSrtTxt);
    
    // Selection Sort
    char selectionTxt[] = "Selection Sort,";
    selectionSrtBtn(selectionTxt);
    
    // Insertion Sort
    char insertionTxt[] = "Insertion Sort,";
    insertionSrtBtn(insertionTxt);
    
    // Quick Sort
    char quickTxt[] = "Quick Sort,";
    quickSrtBtn(quickTxt);
}

void startBtn(char Start[]){
    Button(15, 100, Start, DARKGRAY, shouldStartSorting);
    return;
}

void showOptions(){
    char startTxt[] = "Start Sorting!";
    startBtn(startTxt);
}
//############################################################################################//
void BubbleSort(int arr[]){
    
    int endingPoint = numOfBars;
    bool sortCompleted = false;
    int count = 0;
    
    while(sortCompleted == false){
        
        for (int i=0; i<endingPoint-1; i++){
            
            BeginDrawing();
            
            BarCol[i] = RED;
            DrawBars(arr, randHeights, BarCol);
            
            if (randHeights[i] > randHeights[i+1]){
                std::swap(randHeights[i], randHeights[i+1]);
                std::swap(arr[i], arr[i+1]);
            }
            
            ClearBackground(LIGHTGRAY);
            
            for (int j = numOfBars-1; j>=endingPoint; j--){
                BarCol[j] = GREEN;
            }
            for (int j = i; j>=0; j--){
                BarCol[j] = BLUE;
            }
            EndDrawing();
        }
        
        endingPoint--;
        count++;
        
        if (count == numOfBars){
            sortCompleted = true;
        }
    }
}
//############################################################################################//
void SelectionSort(int arr[]){
    
    int endingpoint = numOfBars;
    bool sortCompleted = false;
    int tracker = 1;
    int smallest;
    
    while(sortCompleted == false){
        
        for(int i=0; i<endingpoint-1; i++){
            
            BeginDrawing();
            
            smallest = randHeights[i];
            
            for(int j=i+1; j<endingpoint; j++){
                if(randHeights[j] < smallest){
                    smallest = randHeights[j];
                    tracker = j;
                }
            }
            
            BarCol[tracker] = PURPLE;
            BarCol[i] = RED;
            ClearBackground(LIGHTGRAY);
            DrawBars(arr, randHeights, BarCol);
            
            EndDrawing();
            
            BarCol[i] = GREEN;
            BarCol[tracker] = BLUE;
    
            if (randHeights[tracker] < randHeights[i] && i<tracker){
                std::swap(randHeights[tracker], randHeights[i]);
                std::swap(arr[tracker], arr[i]);
            }
        }
        
        sortCompleted = true;
    }
}
//############################################################################################//
void InsertionSort(int arr[]){
    
    int endingpoint = numOfBars;
    bool sortCompleted = false;
    int tracker = 0;
    
    while (sortCompleted == false){
        
        for (int i=0; i<endingpoint; i++){

            BeginDrawing();
            
            tracker = i;
            
            ClearBackground(LIGHTGRAY);
            
            while(tracker > 0 && randHeights[tracker-1] > randHeights[tracker]){
                BarCol[tracker] = GREEN;
                std::swap(arr[tracker], arr[tracker-1]);
                std::swap(randHeights[tracker], randHeights[tracker-1]);
                std::swap(BarCol[tracker], BarCol[tracker-1]);
                tracker = tracker-1;
            }
            
            BarCol[tracker] = PURPLE;
            
            BarCol[i] = RED;
            
            DrawBars(arr, randHeights, BarCol);
            
            EndDrawing();
            
            BarCol[tracker] = GREEN;
            
            BarCol[i] = GREEN;
        }
        
        sortCompleted = true;
    }
}
//############################################################################################//
int partition(int arr[], int start, int end){
    
    // select last Bar as the pivot
    int pivot = randHeights[end];
    int pIndex = start;
    
    // compare all Bars to the pivot Bar (last one)
    for (int i=start; i<end; i++){
        ClearBackground(LIGHTGRAY);
        BarCol[end] = GREEN;
        BeginDrawing();
        BarCol[i] = RED;
        BarCol[pIndex] = GREEN;
        BarCol[end] = PURPLE;

        if (randHeights[i] < pivot){
            std::swap(arr[i], arr[pIndex]);
            std::swap(randHeights[i], randHeights[pIndex]);
            //std::swap(BarCol[i], BarCol[pIndex]);
            pIndex++;
            DrawBars(arr, randHeights, BarCol);
        }
        BarCol[pIndex] = RED;
        DrawBars(arr, randHeights, BarCol);
        
        EndDrawing();
        //BarCol[i] = GREEN;
        BarCol[pIndex] = GREEN;
        BarCol[end] = BLUE;
        
        //BarCol[i] = GREEN;
    }
    
    // swap the pivot with the pIndex position (middle)
    std::swap(arr[pIndex], arr[end]);
    std::swap(randHeights[pIndex], randHeights[end]);

    
    //BarCol[end] = RED;
    
    //BarCol[end] = RED;
    //BarCol[pIndex] = GREEN;
    
    return pIndex;
}
void quickSrt(int arr[], int start, int end){
    
    bool sortCompleted = false;
    
    if (start <= end){
    
        int pivot = partition(arr, start, end);
        
        //WaitTime(1.0);
        
        // recursive call for left side
        quickSrt(arr, start, pivot-1);
        
        // recursive call for right side
        quickSrt(arr, pivot+1, end);
        
    }
    
    sortCompleted = true;
    
}
//############################################################################################//
void SortArray(){
    
    if (bubbleSrtPressed){
        BubbleSort(arr);
        shouldStartSorting = false;
        doneSorting = true;
        DrawBars(arr, randHeights, BarCol);
        doneSorting = false;
    }
    if (selectionSrtPressed){
        SelectionSort(arr);
        shouldStartSorting = false;
        doneSorting = true;
        DrawBars(arr, randHeights, BarCol);
        doneSorting = false;
    }
    if (insertionSrtPressed){
        InsertionSort(arr);
        shouldStartSorting = false;
        doneSorting = true;
        DrawBars(arr, randHeights, BarCol);
        doneSorting = false;
    }
    if (quickSrtPressed){
        quickSrt(arr, 0, numOfBars-1);
        shouldStartSorting = false;
        doneSorting = true;
        DrawBars(arr, randHeights, BarCol);
        doneSorting = false;
    }
}

int main(){
    
    // Window Configuration:
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "Sorting Algorithm Visualization");
    SetWindowMinSize(MinWindowWidth, MinWindowHeight);
    
    // Set FPS:
    SetTargetFPS(FPS);
    
    // Main Game Loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        if (shouldShowMenu){
            showMenu();
        }
        
        shouldShowOptions = false;
        if (bubbleSrtPressed || selectionSrtPressed || insertionSrtPressed || quickSrtPressed){
            shouldShowOptions = true;
        }
        
        if (shouldShowOptions){
            showOptions();
        }
        
        if (shouldStartSorting){
            SortArray();
        }

        ClearBackground(RAYWHITE);
        
        //DrawText("Sorting Visualizer", 50, 60, 20, MAROON);
        
        if (shouldRandBars == true){
            RandomizeBars(randHeights);
            doneSorting = false;
        }
        
        if (doneSorting == false){
            for (int i=0; i<numOfBars; i++){
                BarCol[i] = BLUE;
            }
            DrawBars(arr, randHeights, BarCol);
        }
        //DrawBars(arr, randHeights, BarCol);
        
    
        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}
