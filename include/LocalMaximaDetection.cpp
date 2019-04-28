//
//  LocalMaximaDetection Library coded by Brenda Camacho García
//
//

#include <vector>

std::vector<int> LocMax_pw(std::vector<int> dataVector, int minProminence, int maxProminence, int minWidth, int maxWidth)
{

    //Find local maxima
    int dataVectorSize=dataVector.size();
    std::vector<int>localMaximaIndex,localMaximaValue,prominenceValue, inRangeLocalMaxima;
    int j;
    int currentValue, nextValue, prevValue;
    int totalLocalMaxima;
    int prevLocalMaximumIndex;
    int nextLocalMaximumIndex;
    int prevHigherLocalMaximaValue;
    int nextHigherLocalMaximaValue;
    int leftWidth, rightWidth, width;
    int prevMinimum, nextMinimum, minimumValue;
    int prominence;
    int i=1;
/********************* FIND LOCAL MAXIMA ***************************/
//  Compare the previous, current and next points
//  current point is a local maximum if:
//  * Previous and next point values are lower than current point value
//  * Current point value is equal to previous points, and then next value is lower
    while (i<dataVectorSize)
    {
        j=1;
        currentValue=dataVector[i];
        prevValue=dataVector[i-1];
        nextValue=dataVector[i+j];

        if ((prevValue<currentValue)&&(currentValue>=nextValue))
        {
            while ((currentValue==nextValue)&&((i+j)<dataVectorSize))
            {
                j++;
                nextValue=dataVector[i+j];
            }
            if (currentValue>nextValue)
            {
                //If it is a local maximum then append the value to the LocalMaximaValue vector and save the location
                // in localMaximaIndex vector
                localMaximaIndex.push_back(i);
                localMaximaValue.push_back(currentValue);
            }
        }
        i+=j;
    }

    totalLocalMaxima=localMaximaIndex.size();
    prominenceValue.erase(prominenceValue.begin(),prominenceValue.end());

/********************* GET PROMINENCE ***************************/

// To get the prominence:
//  1. Look for a higher previous LocalMaximum (prevLocalMaximumValue, prevLocalMaximumIndex);
//  2. Look for a higher later LocalMaximum (nextLocalMaximumValue, nextLocalMaximumIndex);
//  3. Look for the minimum point value between the current local maximum and a higher previous one
//  4. Look for the minimum point value between the current local maximum and a higher later one
//  5. Get the minimum of both values (minimumValue).
//  6. Prominence will be equal to current LocalMaxima[i] -minimumValue


    for (i=0;i<totalLocalMaxima;i++)
    {
        prevLocalMaximumIndex=i-1;
        nextLocalMaximumIndex=i+1;
        prevHigherLocalMaximaValue=0;
        nextHigherLocalMaximaValue=0;
    ////  1. Look for a higher previous LocalMaximum (prevLocalMaximumValue, prevLocalMaximumIndex);
        if (prevLocalMaximumIndex>=0)
        {
            while ((prevLocalMaximumIndex>=1)&&(localMaximaValue[prevLocalMaximumIndex]<=localMaximaValue[i]))
            {
                prevLocalMaximumIndex--;
            }
            if (localMaximaValue[prevLocalMaximumIndex]>localMaximaValue[i]){
                prevHigherLocalMaximaValue=localMaximaValue[prevLocalMaximumIndex];
            } else {
                prevHigherLocalMaximaValue=0;
            }
        }
    ////  2. Look for a higher later LocalMaximum (nextLocalMaximumValue, nextLocalMaximumIndex);

        if (nextLocalMaximumIndex<totalLocalMaxima)
        {
            while ((nextLocalMaximumIndex<totalLocalMaxima-1)&&(localMaximaValue[nextLocalMaximumIndex]<=localMaximaValue[i]))//
            {
                nextLocalMaximumIndex++;
            }
            if (localMaximaValue[nextLocalMaximumIndex]>localMaximaValue[i]){
                nextHigherLocalMaximaValue=localMaximaValue[nextLocalMaximumIndex];
            } else {
                nextHigherLocalMaximaValue=0;
            }
        }
        prevMinimum=dataVector[localMaximaIndex[i]];
        nextMinimum=dataVector[localMaximaIndex[i]];
        minimumValue=dataVector[localMaximaIndex[i]];
        ////  3. Look for the minimum point value between the current local maximum and a higher previous one
        if ((prevHigherLocalMaximaValue==0)&&(nextHigherLocalMaximaValue==0))
        //Current Local Maximum is the highest, so look for the minimum of all the vector values
        {
            for (j=0;j<dataVectorSize;j++)
            {
                if (dataVector[j]<minimumValue)
                    minimumValue=dataVector[j];
            }


        }
        else
        {
            if (prevLocalMaximumIndex<0)
                //Current Local Maximum is the first, so there is no previous one. Search from the beginning to the current
                // LocalMaxima Index
            {
                for (j=localMaximaIndex[i];j>=0;j--)
                {
                    if (dataVector[j]<prevMinimum)
                        prevMinimum=dataVector[j];
                }

            }
            else
            {
                for (j=localMaximaIndex[i];j>localMaximaValue[prevLocalMaximumIndex];j--)
                {
                    if (dataVector[j]<prevMinimum)
                        prevMinimum=dataVector[j];
                }

            }
        ////  4. Look for the minimum point value between the current local maximum and a higher later one

            if (nextLocalMaximumIndex>=totalLocalMaxima-1)
            {
                //Current Local Maximum is the last, so there is no later one. Search from the current LocalMaxima Index
                // to the last value.
                for (j=localMaximaIndex[i];j<dataVectorSize;j++)
                {
                    if (dataVector[j]<nextMinimum)
                        nextMinimum=dataVector[j];
                }

            }
            else
            {
                for (j=localMaximaIndex[i];j<localMaximaIndex[nextLocalMaximumIndex];j++)
                {
                    if (dataVector[j]<nextMinimum)
                        nextMinimum=dataVector[j];
                }

            }
        ////  5. Get the minimum of both values (minimumValue).

            minimumValue= prevMinimum>nextMinimum? prevMinimum:nextMinimum;
        }
        ////  6. Prominence will be equal to current LocalMaxima[i] -minimumValue
        prominence=localMaximaValue[i]-minimumValue;
/*************************** GET WIDTH ********************************/
// Calculate the width of the peak at prominence/2

        j=1;
        while (((localMaximaIndex[i]-j)>0)&&(dataVector[localMaximaIndex[i]-j]-minimumValue>(prominence)/2)) { j++;}
        leftWidth=j;
        j=1;
        while (((localMaximaIndex[i]+j)<dataVectorSize)&&(dataVector[localMaximaIndex[i]+j]-minimumValue>(prominence)/2)) { j++;}
        rightWidth=j;
        int width=leftWidth+rightWidth;

/********************* IS THE PEAK IN RANGE? ***************************/
// If the peak is between the prominence and width ranges provided, append the value to the output vector
        if ((localMaximaValue[i]-minimumValue>=minProminence)&&(localMaximaValue[i]-minimumValue<=maxProminence)&&(width>=minWidth)&&(width<=maxWidth))
        {
            inRangeLocalMaxima.push_back(localMaximaIndex[i]);
        }

    }
    return inRangeLocalMaxima;
}
