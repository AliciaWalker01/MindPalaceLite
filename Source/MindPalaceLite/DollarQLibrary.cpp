// Fill out your copyright notice in the Description page of Project Settings.

#include "DollarQLibrary.h"


float UDollarQLibrary::SqrEuclideanDistance(FDPoint a, FDPoint b)
{
	return pow((a.X - b.X), 2) + pow((a.Y - b.Y), 2);
}

float UDollarQLibrary::EuclideanDistance(FDPoint a, FDPoint b)
{
	return sqrt(SqrEuclideanDistance(a, b));
}

float UDollarQLibrary::PathLength(TArray<FDPoint> points)
{
	float d = 0.0f;
	for (int i = 1; i < points.Num(); i++)
	{
		if (points[i].StrokeID == points[i - 1].StrokeID) {
			d = d + EuclideanDistance(points[i - 1], points[i]);
		}
	}
	return d;
}

TArray<FIntArray> UDollarQLibrary::ConstructLUT(TArray<FDPoint> points, int32 n, int32 m, int32 SF)
{
	TArray<FIntArray> LUT;

	LUT.SetNum(m);
	for (int32 i = 0; i < m; i++)
	{
		LUT[i].A.SetNum(m);
	}

	for (int32 i = 0; i < m; i++)
	{
		for (int32 j = 0; j < m; j++)
		{
			int32 minDistance = TNumericLimits<int32>::Max();
			int32 indexMin = -1;
			for (int32 t = 0; t < points.Num(); t++)
			{
				int32 row = points[t].intY / SF;
				int32 col = points[t].intX / SF;
				int32 dist = (row - i)*(row - i) + (col - j)*(col - j);
				if (dist < minDistance)
				{
					minDistance = dist;
					indexMin = t;
				}

			}
			LUT[i].A[j] = indexMin;
		}

	}
	return LUT;
}

TArray<FDPoint> UDollarQLibrary::Resample(TArray<FDPoint> points, int32 n)
{
	float I = PathLength(points) / (n - 1);
	float D = 0;

	FDPoint newpoint;
	newpoint.X = points[0].X;
	newpoint.Y = points[0].Y;
	newpoint.StrokeID = points[0].StrokeID;
	newpoint.intX = points[0].intX;
	newpoint.intY = points[0].intY;

	TArray<FDPoint> newPoints;
	newPoints.SetNum(n);
	newPoints[0] = (newpoint);

	int32 numPoints = 1;

	for (int32 i = 1; i < points.Num(); i++)
	{
		if (points[i].StrokeID == points[i - 1].StrokeID)
		{
			float d = EuclideanDistance(points[i - 1], points[i]);
			if (D + d >= I)
			{
				FDPoint firstpoint = points[i - 1];
				while (D + d >= I)
				{
					float t = std::fmin(fmax((I - D) / d, 0.0f), 1.0f);
					if (std::isnan(t)) t = 0.5f;

					newpoint.X = (1.0f - t)*firstpoint.X + t * points[i].X;
					newpoint.Y = (1.0f - t)*firstpoint.Y + t * points[i].Y;
					newpoint.StrokeID = points[i].StrokeID;
					newpoint.intY = points[i].intY;
					newpoint.intX = points[1].intY;

					d = D + d - I;
					D = 0;
					newPoints[numPoints++] = newpoint;
					firstpoint = newPoints[numPoints - 1];
				};

				D = d;
			}
			else
			{
				D += d;
			}
		}
	}
	if (numPoints == n - 1)
	{
		newpoint.X = points[points.Num() - 1].X;
		newpoint.Y = points[points.Num() - 1].Y;
		newpoint.StrokeID = points[points.Num() - 1].StrokeID;
		newpoint.intX = points[points.Num() - 1].intX;
		newpoint.intY = points[points.Num() - 1].intY;
		newPoints[numPoints++] = newpoint;
	}

	return newPoints;
}

TArray<FDPoint> UDollarQLibrary::Scale(TArray<FDPoint> points)
{
	float minx = std::numeric_limits<float>::max();
	float miny = std::numeric_limits<float>::max();
	float maxx = std::numeric_limits<float>::min();
	float maxy = std::numeric_limits<float>::min();

	for (int32 i = 0; i < points.Num(); i++)
	{
		if (minx > points[i].X) minx = points[i].X;
		if (miny > points[i].Y) miny = points[i].Y;
		if (maxx < points[i].X) maxx = points[i].X;
		if (maxy < points[i].Y) maxy = points[i].Y;
	}
	TArray<FDPoint> newpoints;
	newpoints.SetNum(points.Num());
	float scale = std::max(maxx - minx, maxy - miny);
	for (int32 i = 0; i < points.Num(); i++)
	{
		FDPoint newpoint;
		newpoint.X = (points[i].X - minx) / scale;
		newpoint.Y = (points[i].Y - miny) / scale;
		newpoint.StrokeID = points[i].StrokeID;
		newpoint.intX = 0;
		newpoint.intY = 0;
		newpoints[i] = newpoint;
	}

	return newpoints;
}

TArray<FDPoint> UDollarQLibrary::GenerateSquare()
{
	TArray<FDPoint> test;
	for (int32 i = 1; i < 20; i++)
	{
		for (int32 j = 1; j < 20; j++)
		{
			FDPoint test2;
			test2.X = i;
			test2.Y = j;
			test2.intX = 0;
			test2.intY = 0;
			test2.StrokeID = 0;

			test.Add(test2);
		}
	}

	return test;
}

FDPoint UDollarQLibrary::Centroid(TArray<FDPoint> points)
{
	float cx = 0.0f;
	float cy = 0.0f;
	for (int32 i = 0; i < points.Num(); i++)
	{
		cx += points[i].X;
		cy += points[i].Y;
	}
	FDPoint newpoint;
	newpoint.X = cx / points.Num();
	newpoint.Y = cy / points.Num();
	newpoint.StrokeID = 0;
	newpoint.intY = 0;
	newpoint.intX = 0;

	return newpoint;
}

TArray<FDPoint> UDollarQLibrary::TranslateTo(TArray<FDPoint> points, FDPoint point)
{
	TArray<FDPoint> newpoints;
	newpoints.SetNum(points.Num());
	for (int32 i = 0; i < points.Num(); i++)
	{
		FDPoint newpoint;
		newpoint.X = points[i].X - point.X;
		newpoint.Y = points[i].Y - point.Y;
		newpoint.StrokeID = points[i].StrokeID;
		newpoint.intX = 0;
		newpoint.intY = 0;
		newpoints[i] = newpoint;
	}
	return newpoints;

}

TArray<FDPoint> UDollarQLibrary::TransformCoordsToIntegers(TArray<FDPoint> points, int32 Max_Int_Coordinates)
{
	TArray<FDPoint> npoints = points;

	for (int32 i = 0; i < points.Num(); i++)
	{
		npoints[i].intX = (int32)((points[i].X + 1.0f) / 2.0f * (Max_Int_Coordinates - 1));
		npoints[i].intY = (int32)((points[i].Y + 1.0f) / 2.0f*(Max_Int_Coordinates - 1));

	}

	return npoints;
}

TArray<float> UDollarQLibrary::ComputeLowerBound(TArray<FDPoint> points1, TArray<FDPoint> points2, TArray<FIntArray> LUT, int32 step, int32 SF)
{
	int32 n = points1.Num();
	TArray<float> LB;
	LB.SetNum(n / step + 1);
	TArray<float> SAT;
	SAT.SetNum(n);

	LB[0] = 0;
	for (int32 i = 0; i < n; i++)
	{
		int32 index = LUT[points1[i].intY / SF].A[points1[i].intX / SF];
		float dist = SqrEuclideanDistance(points1[i], points2[index]);
		SAT[i] = (i == 0) ? dist : SAT[i - 1] + dist;
		LB[0] += (n - 1)*dist;

	}
	for (int32 i = step, indexLB = 1; i < n; i += step, indexLB++)
	{
		LB[indexLB] = LB[0] + i * SAT[n - 1] - n * SAT[i - 1];
	}
	return LB;

}

float UDollarQLibrary::CloudDistance(TArray<FDPoint> points1, TArray<FDPoint> points2, int32 startIndex, float minSoFar, bool UseEarlyAbandoning)
{
	int32 nn = points1.Num();
	TArray < int32> indexesNotMatched;
	indexesNotMatched.SetNum(nn);

	for (int32 j = 0; j < nn; j++)
	{
		indexesNotMatched[j] = j;
	}

	float sum = 0;
	int32 i = startIndex;
	int32 weight = nn;
	int32 indexNotMatched = 0;
	do
	{
		int32 index = -1;
		float minDistance = TNumericLimits<float>::Max();
		for (int32 j = indexNotMatched; j < nn; j++)
		{
			float dist = SqrEuclideanDistance(points1[i], points2[indexesNotMatched[j]]);
			if (dist < minDistance)
			{
				minDistance = dist;
				index = j;
			}
		}
		indexesNotMatched[index] = indexesNotMatched[indexNotMatched];
		sum += (weight--)*minDistance;

		if (UseEarlyAbandoning)
		{
			if (sum >= minSoFar)
			{
				return sum;
			}
		}

		i = (i + 1) % nn;
		indexNotMatched++;
	} while (i != startIndex);


	return sum;
}

float UDollarQLibrary::CloudMatch(TArray<FDPoint> points1, TArray<FDPoint> points2, TArray<FIntArray> LUT1, TArray<FIntArray> LUT2, float minSoFar, bool UseLowerBounding, bool UseEarlyAbandoning, int32 SF)
{
	int32 nn = points1.Num();
	float eps = 0.5f;
	int32 step = (int32)floor(pow(nn, 1.0f - eps));

	if (UseLowerBounding)
	{
		TArray<float> LB1 = ComputeLowerBound(points1, points2, LUT1, step, SF);
		TArray<float> LB2 = ComputeLowerBound(points2, points1, LUT2, step, SF);
		for (int32 i = 0, indexLB = 0; i < nn; i += step, indexLB++)
		{
			if (LB1[indexLB] < minSoFar) minSoFar = std::min(minSoFar, CloudDistance(points1, points2, i, minSoFar, UseEarlyAbandoning));
			if (LB2[indexLB] < minSoFar) minSoFar = std::min(minSoFar, CloudDistance(points2, points1, i, minSoFar, UseEarlyAbandoning));
		}
	}
	else
	{
		for (int32 i = 0; i < nn; i += step)
		{
			minSoFar = std::min(minSoFar, CloudDistance(points1, points2, i, minSoFar, UseEarlyAbandoning));
			minSoFar = std::min(minSoFar, CloudDistance(points2, points1, i, minSoFar, UseEarlyAbandoning));
		}
	}

	return minSoFar;
}

TArray<FDPoint> UDollarQLibrary::Normalise(TArray<FDPoint> points, int32 n, int32 m, int32 maxintcoords)
{
	TArray<FDPoint> temppoints = Resample(points, n);
	FDPoint centrepoint = Centroid(temppoints);
	temppoints = TranslateTo(temppoints, centrepoint);
	temppoints = Scale(temppoints);
	temppoints = TransformCoordsToIntegers(temppoints, maxintcoords);

	return temppoints;
}

FString UDollarQLibrary::Recognizer(TArray<FDPoint> NormalisedPoints, TArray<FIntArray> InputLUT, TArray<FDPoints> NormalisedTemplates, int32 n, int32 m, int32 maxintcoords, bool UseLowerBounding, bool UseEarlyAbandoning)
{
	float Score = TNumericLimits<float>::Max();

	FString result;
	float d = 0;
	for (int32 i = 0; i < NormalisedTemplates.Num(); i++)
	{
		d = CloudMatch(NormalisedPoints, NormalisedTemplates[i].points, InputLUT, NormalisedTemplates[i].LUT, Score, UseLowerBounding, UseEarlyAbandoning, maxintcoords / m);
		if (d < Score)
		{
			Score = d;
			result = NormalisedTemplates[i].name;
		}
	}
	return result;
}
