#include "matrix_4.hpp"
#include <cmath>

namespace Engine
{
	//Default constructor initializes the matrix with its identity
	matrix_4::matrix_4()
	{
		set_identity();
	}

	//Takes 16 parameters, assigned in column major order
	matrix_4::matrix_4(float value1, float value2, float value3, float value4, float value5, float value6, float value7, float value8, float value9, float value10, float value11, float value12, float value13, float value14, float value15, float value16)
	{
		mMatrix[0] = value1;
		mMatrix[1] = value2;
		mMatrix[2] = value3;
		mMatrix[3] = value4;

		mMatrix[4] = value5;
		mMatrix[5] = value6;
		mMatrix[6] = value7;
		mMatrix[7] = value8;

		mMatrix[8] = value9;
		mMatrix[9] = value10;
		mMatrix[10] = value11;
		mMatrix[11] = value12;

		mMatrix[12] = value13;
		mMatrix[13] = value14;
		mMatrix[14] = value15;
		mMatrix[15] = value16;
	}

	//Takes an array with 16 positions
	matrix_4::matrix_4(float pValues[16])
	{
		mMatrix[0] = pValues[0];
		mMatrix[1] = pValues[1];
		mMatrix[2] = pValues[2];
		mMatrix[3] = pValues[3];

		mMatrix[4] = pValues[4];
		mMatrix[5] = pValues[5];
		mMatrix[6] = pValues[6];
		mMatrix[7] = pValues[7];

		mMatrix[8] = pValues[8];
		mMatrix[9] = pValues[9];
		mMatrix[10] = pValues[10];
		mMatrix[11] = pValues[11];

		mMatrix[12] = pValues[12];
		mMatrix[13] = pValues[13];
		mMatrix[14] = pValues[14];
		mMatrix[15] = pValues[15];
	}


	matrix_4::~matrix_4()
	{
	}

	//Set the matrix to its identity
	void matrix_4::set_identity()
	{
		mMatrix[0] = 1;
		mMatrix[1] = 0;
		mMatrix[2] = 0;
		mMatrix[3] = 0;

		mMatrix[4] = 0;
		mMatrix[5] = 1;
		mMatrix[6] = 0;
		mMatrix[7] = 0;

		mMatrix[8] = 0;
		mMatrix[9] = 0;
		mMatrix[10] = 1;
		mMatrix[11] = 0;

		mMatrix[12] = 0;
		mMatrix[13] = 0;
		mMatrix[14] = 0;
		mMatrix[15] = 1;
	}

	//Returns the euclidean angle os the matrix
	Vector_3 matrix_4::get_angle()
	{
		Vector_3 euclideanAngle;

		if (mMatrix[0] == 1.0f || mMatrix[0] == -1.0f)
		{
			euclideanAngle.mX = 0; //Pitch
			euclideanAngle.mY = atan2f(mMatrix[8], mMatrix[14]); //Yaw
			euclideanAngle.mZ = 0; //Roll
		}
		else
		{
			euclideanAngle.mX = asinf(mMatrix[1]); //Pitch
			euclideanAngle.mY = atan2f(-mMatrix[2], mMatrix[0]); //Yaw
			euclideanAngle.mZ = atan2f(-mMatrix[9], mMatrix[5]); //Roll
		}

		return euclideanAngle;
	}

	//Translate the matrix
	matrix_4 matrix_4::translate(Vector_4 pTranslation)
	{
		matrix_4 newMatrix = matrix_4();
		newMatrix.mMatrix[3] = pTranslation.mX;
		newMatrix.mMatrix[7] = pTranslation.mY;
		newMatrix.mMatrix[11] = pTranslation.mZ;
		return newMatrix;
	}

	//Rotates the matrix in th X axis
	matrix_4 matrix_4::rotate_x(float angle)
	{
		matrix_4 newMatrix = matrix_4();
		newMatrix.mMatrix[5] = std::cos(-angle);
		newMatrix.mMatrix[6] = -std::sin(-angle);
		newMatrix.mMatrix[9] = std::sin(-angle);
		newMatrix.mMatrix[10] = std::cos(-angle);
		return newMatrix;
	}

	//Rotates the matrix in th Y axis
	matrix_4 matrix_4::rotate_y(float angle)
	{
		matrix_4 newMatrix = matrix_4();
		newMatrix.mMatrix[0] = std::cos(-angle);
		newMatrix.mMatrix[2] = std::sin(-angle);
		newMatrix.mMatrix[8] = -std::sin(-angle);
		newMatrix.mMatrix[10] = std::cos(-angle);
		return newMatrix;
	}

	//Rotates the matrix in th Z axis
	matrix_4 matrix_4::rotate_z(float angle)
	{
		matrix_4 newMatrix = matrix_4();
		newMatrix.mMatrix[0] = std::cos(-angle);
		newMatrix.mMatrix[1] = -std::sin(-angle);
		newMatrix.mMatrix[4] = std::sin(-angle);
		newMatrix.mMatrix[5] = std::cos(-angle);
		return newMatrix;
	}

	//Returns the matrix
	float* Engine::matrix_4::get_matrix()
	{
		return mMatrix;
	}

	//Returns the inverse of the matrix
	matrix_4 matrix_4::get_invert()
	{
		float determinant;
		matrix_4 inverse, matrixCopy;
		matrixCopy = *this;

		inverse.mMatrix[0] =	matrixCopy.mMatrix[5] *  matrixCopy.mMatrix[10] * matrixCopy.mMatrix[15] -
								matrixCopy.mMatrix[5] *  matrixCopy.mMatrix[11] * matrixCopy.mMatrix[14] -
								matrixCopy.mMatrix[9] *  matrixCopy.mMatrix[6] *  matrixCopy.mMatrix[15] +
								matrixCopy.mMatrix[9] *  matrixCopy.mMatrix[7] *  matrixCopy.mMatrix[14] +
								matrixCopy.mMatrix[13] * matrixCopy.mMatrix[6] *  matrixCopy.mMatrix[11] -
								matrixCopy.mMatrix[13] * matrixCopy.mMatrix[7] *  matrixCopy.mMatrix[10];

		inverse.mMatrix[4] =   -matrixCopy.mMatrix[4] *  matrixCopy.mMatrix[10] * matrixCopy.mMatrix[15] +
								 matrixCopy.mMatrix[4] *  matrixCopy.mMatrix[11] * matrixCopy.mMatrix[14] +
								 matrixCopy.mMatrix[8] *  matrixCopy.mMatrix[6] *  matrixCopy.mMatrix[15] -
								 matrixCopy.mMatrix[8] *  matrixCopy.mMatrix[7] *  matrixCopy.mMatrix[14] -
								 matrixCopy.mMatrix[12] * matrixCopy.mMatrix[6] *  matrixCopy.mMatrix[11] +
								 matrixCopy.mMatrix[12] * matrixCopy.mMatrix[7] *  matrixCopy.mMatrix[10];

		inverse.mMatrix[8] =	 matrixCopy[4] * matrixCopy[9] * matrixCopy[15] -
								 matrixCopy[4] * matrixCopy[11] * matrixCopy[13] -
								 matrixCopy[8] * matrixCopy[5] * matrixCopy[15] +
								 matrixCopy[8] * matrixCopy[7] * matrixCopy[13] +
								 matrixCopy[12] * matrixCopy[5] * matrixCopy[11] -
								 matrixCopy[12] * matrixCopy[7] * matrixCopy[9];

		inverse.mMatrix[12] = -matrixCopy[4] * matrixCopy[9] * matrixCopy[14] +
			matrixCopy[4] * matrixCopy[10] * matrixCopy[13] +
			matrixCopy[8] * matrixCopy[5] * matrixCopy[14] -
			matrixCopy[8] * matrixCopy[6] * matrixCopy[13] -
			matrixCopy[12] * matrixCopy[5] * matrixCopy[10] +
			matrixCopy[12] * matrixCopy[6] * matrixCopy[9];

		inverse[1] = -matrixCopy[1] * matrixCopy[10] * matrixCopy[15] +
			matrixCopy[1] * matrixCopy[11] * matrixCopy[14] +
			matrixCopy[9] * matrixCopy[2] * matrixCopy[15] -
			matrixCopy[9] * matrixCopy[3] * matrixCopy[14] -
			matrixCopy[13] * matrixCopy[2] * matrixCopy[11] +
			matrixCopy[13] * matrixCopy[3] * matrixCopy[10];

		inverse[5] = matrixCopy[0] * matrixCopy[10] * matrixCopy[15] -
			matrixCopy[0] * matrixCopy[11] * matrixCopy[14] -
			matrixCopy[8] * matrixCopy[2] * matrixCopy[15] +
			matrixCopy[8] * matrixCopy[3] * matrixCopy[14] +
			matrixCopy[12] * matrixCopy[2] * matrixCopy[11] -
			matrixCopy[12] * matrixCopy[3] * matrixCopy[10];

		inverse[9] = -matrixCopy[0] * matrixCopy[9] * matrixCopy[15] +
			matrixCopy[0] * matrixCopy[11] * matrixCopy[13] +
			matrixCopy[8] * matrixCopy[1] * matrixCopy[15] -
			matrixCopy[8] * matrixCopy[3] * matrixCopy[13] -
			matrixCopy[12] * matrixCopy[1] * matrixCopy[11] +
			matrixCopy[12] * matrixCopy[3] * matrixCopy[9];

		inverse[13] = matrixCopy[0] * matrixCopy[9] * matrixCopy[14] -
			matrixCopy[0] * matrixCopy[10] * matrixCopy[13] -
			matrixCopy[8] * matrixCopy[1] * matrixCopy[14] +
			matrixCopy[8] * matrixCopy[2] * matrixCopy[13] +
			matrixCopy[12] * matrixCopy[1] * matrixCopy[10] -
			matrixCopy[12] * matrixCopy[2] * matrixCopy[9];

		inverse[2] = matrixCopy[1] * matrixCopy[6] * matrixCopy[15] -
			matrixCopy[1] * matrixCopy[7] * matrixCopy[14] -
			matrixCopy[5] * matrixCopy[2] * matrixCopy[15] +
			matrixCopy[5] * matrixCopy[3] * matrixCopy[14] +
			matrixCopy[13] * matrixCopy[2] * matrixCopy[7] -
			matrixCopy[13] * matrixCopy[3] * matrixCopy[6];

		inverse[6] = -matrixCopy[0] * matrixCopy[6] * matrixCopy[15] +
			matrixCopy[0] * matrixCopy[7] * matrixCopy[14] +
			matrixCopy[4] * matrixCopy[2] * matrixCopy[15] -
			matrixCopy[4] * matrixCopy[3] * matrixCopy[14] -
			matrixCopy[12] * matrixCopy[2] * matrixCopy[7] +
			matrixCopy[12] * matrixCopy[3] * matrixCopy[6];

		inverse[10] = matrixCopy[0] * matrixCopy[5] * matrixCopy[15] -
			matrixCopy[0] * matrixCopy[7] * matrixCopy[13] -
			matrixCopy[4] * matrixCopy[1] * matrixCopy[15] +
			matrixCopy[4] * matrixCopy[3] * matrixCopy[13] +
			matrixCopy[12] * matrixCopy[1] * matrixCopy[7] -
			matrixCopy[12] * matrixCopy[3] * matrixCopy[5];

		inverse[14] = -matrixCopy[0] * matrixCopy[5] * matrixCopy[14] +
			matrixCopy[0] * matrixCopy[6] * matrixCopy[13] +
			matrixCopy[4] * matrixCopy[1] * matrixCopy[14] -
			matrixCopy[4] * matrixCopy[2] * matrixCopy[13] -
			matrixCopy[12] * matrixCopy[1] * matrixCopy[6] +
			matrixCopy[12] * matrixCopy[2] * matrixCopy[5];

		inverse[3] = -matrixCopy[1] * matrixCopy[6] * matrixCopy[11] +
			matrixCopy[1] * matrixCopy[7] * matrixCopy[10] +
			matrixCopy[5] * matrixCopy[2] * matrixCopy[11] -
			matrixCopy[5] * matrixCopy[3] * matrixCopy[10] -
			matrixCopy[9] * matrixCopy[2] * matrixCopy[7] +
			matrixCopy[9] * matrixCopy[3] * matrixCopy[6];

		inverse[7] = matrixCopy[0] * matrixCopy[6] * matrixCopy[11] -
			matrixCopy[0] * matrixCopy[7] * matrixCopy[10] -
			matrixCopy[4] * matrixCopy[2] * matrixCopy[11] +
			matrixCopy[4] * matrixCopy[3] * matrixCopy[10] +
			matrixCopy[8] * matrixCopy[2] * matrixCopy[7] -
			matrixCopy[8] * matrixCopy[3] * matrixCopy[6];

		inverse[11] = -matrixCopy[0] * matrixCopy[5] * matrixCopy[11] +
			matrixCopy[0] * matrixCopy[7] * matrixCopy[9] +
			matrixCopy[4] * matrixCopy[1] * matrixCopy[11] -
			matrixCopy[4] * matrixCopy[3] * matrixCopy[9] -
			matrixCopy[8] * matrixCopy[1] * matrixCopy[7] +
			matrixCopy[8] * matrixCopy[3] * matrixCopy[5];

		inverse[15] = matrixCopy[0] * matrixCopy[5] * matrixCopy[10] -
			matrixCopy[0] * matrixCopy[6] * matrixCopy[9] -
			matrixCopy[4] * matrixCopy[1] * matrixCopy[10] +
			matrixCopy[4] * matrixCopy[2] * matrixCopy[9] +
			matrixCopy[8] * matrixCopy[1] * matrixCopy[6] -
			matrixCopy[8] * matrixCopy[2] * matrixCopy[5];

		determinant = (matrixCopy[0] * inverse[0]) + (matrixCopy[1] * inverse[4]) + (matrixCopy[2] * inverse[8]) + (matrixCopy[3] * inverse[12]);

		if (determinant == 0)
		{
			return NULL;
		}
		else
		{
			//Calculates the inverse by multiplying the inverse of the determinant with the adjunt matrix
			determinant = 1 / determinant;
			for (int i = 0; i < 16; i++)
			{
				inverse[i] = inverse[i] * determinant;
			}

			return inverse;
		}
	}

	matrix_4 matrix_4::get_transpose()
	{
		matrix_4 transposedMatrix;

		transposedMatrix[1] = mMatrix[4];
		transposedMatrix[2] = mMatrix[8];
		transposedMatrix[3] = mMatrix[12];

		transposedMatrix[4] = mMatrix[1];
		transposedMatrix[6] = mMatrix[9];
		transposedMatrix[7] = mMatrix[13];

		transposedMatrix[8] = mMatrix[2];
		transposedMatrix[9] = mMatrix[6];
		transposedMatrix[11] = mMatrix[14];

		transposedMatrix[12] = mMatrix[3];
		transposedMatrix[13] = mMatrix[7];
		transposedMatrix[14] = mMatrix[11];

		return transposedMatrix;
	}

	//To manage a single index
	/*float& matrix_4::operator[][](const int pIndex)
	{
		int rowIndex = pIndex % 4;
		int columnIndex = pIndex / 4;
		return mMatrix.mArray[rowIndex][columnIndex];
	}*/

	//To print the matrix
	std::ostream & operator<<(std::ostream &pOs, const matrix_4 &pMatrix)
	{
		pOs << pMatrix.mMatrix[0] << " ";
		pOs << pMatrix.mMatrix[4] << " ";
		pOs << pMatrix.mMatrix[8] << " ";
		pOs << pMatrix.mMatrix[12] << " ";
		pOs << std::endl;
		  
		pOs << pMatrix.mMatrix[1] << " ";
		pOs << pMatrix.mMatrix[5] << " ";
		pOs << pMatrix.mMatrix[9] << " ";
		pOs << pMatrix.mMatrix[13] << " ";
		pOs << std::endl;
		  
		pOs << pMatrix.mMatrix[2] << " ";
		pOs << pMatrix.mMatrix[6] << " ";
		pOs << pMatrix.mMatrix[10] << " ";
		pOs << pMatrix.mMatrix[14] << " ";
		pOs << std::endl;
		  
		pOs << pMatrix.mMatrix[3] << " ";
		pOs << pMatrix.mMatrix[7] << " ";
		pOs << pMatrix.mMatrix[11] << " ";
		pOs << pMatrix.mMatrix[15] << " ";
		pOs << std::endl;

		return pOs;
	}

	Engine::matrix_4 & Engine::matrix_4::operator=(const matrix_4 &pToEqual)
	{
		mMatrix[0] = pToEqual.mMatrix[0];
		mMatrix[1] = pToEqual.mMatrix[1];
		mMatrix[2] = pToEqual.mMatrix[2];
		mMatrix[3] = pToEqual.mMatrix[3];

		mMatrix[4] = pToEqual.mMatrix[4];
		mMatrix[5] = pToEqual.mMatrix[5];
		mMatrix[6] = pToEqual.mMatrix[6];
		mMatrix[7] = pToEqual.mMatrix[7];

		mMatrix[8] = pToEqual.mMatrix[8];
		mMatrix[9] = pToEqual.mMatrix[9];
		mMatrix[10] = pToEqual.mMatrix[10];
		mMatrix[11] = pToEqual.mMatrix[11];

		mMatrix[12] = pToEqual.mMatrix[12];
		mMatrix[13] = pToEqual.mMatrix[13];
		mMatrix[14] = pToEqual.mMatrix[14];
		mMatrix[15] = pToEqual.mMatrix[15];

		return *this;
	}

	Engine::matrix_4 Engine::matrix_4::operator+(const matrix_4 &pToAdd) const
	{
		matrix_4 newMatrix;

		newMatrix.mMatrix[0] = newMatrix.mMatrix[0] + pToAdd.mMatrix[0];
		newMatrix.mMatrix[1] = newMatrix.mMatrix[1] + pToAdd.mMatrix[1];
		newMatrix.mMatrix[2] = newMatrix.mMatrix[2] + pToAdd.mMatrix[2];
		newMatrix.mMatrix[3] = newMatrix.mMatrix[3] + pToAdd.mMatrix[3];

		newMatrix.mMatrix[4] = newMatrix.mMatrix[4] + pToAdd.mMatrix[4];
		newMatrix.mMatrix[5] = newMatrix.mMatrix[5] + pToAdd.mMatrix[5];
		newMatrix.mMatrix[6] = newMatrix.mMatrix[6] + pToAdd.mMatrix[6];
		newMatrix.mMatrix[7] = newMatrix.mMatrix[7] + pToAdd.mMatrix[7];

		newMatrix.mMatrix[8] = newMatrix.mMatrix[8] + pToAdd.mMatrix[8];
		newMatrix.mMatrix[9] = newMatrix.mMatrix[9] + pToAdd.mMatrix[9];
		newMatrix.mMatrix[10] = newMatrix.mMatrix[10] + pToAdd.mMatrix[10];
		newMatrix.mMatrix[11] = newMatrix.mMatrix[11] + pToAdd.mMatrix[11];

		newMatrix.mMatrix[12] = newMatrix.mMatrix[12] + pToAdd.mMatrix[12];
		newMatrix.mMatrix[13] = newMatrix.mMatrix[13] + pToAdd.mMatrix[13];
		newMatrix.mMatrix[14] = newMatrix.mMatrix[14] + pToAdd.mMatrix[14];
		newMatrix.mMatrix[15] = newMatrix.mMatrix[15] + pToAdd.mMatrix[15];

		return newMatrix;
	}

	matrix_4 matrix_4::operator-(const matrix_4 &pToSubstract) const
	{
		matrix_4 newMatrix;

		newMatrix.mMatrix[0] = newMatrix.mMatrix[0] - pToSubstract.mMatrix[0];
		newMatrix.mMatrix[1] = newMatrix.mMatrix[1] - pToSubstract.mMatrix[1];
		newMatrix.mMatrix[2] = newMatrix.mMatrix[2] - pToSubstract.mMatrix[2];
		newMatrix.mMatrix[3] = newMatrix.mMatrix[3] - pToSubstract.mMatrix[3];

		newMatrix.mMatrix[4] = newMatrix.mMatrix[4] - pToSubstract.mMatrix[4];
		newMatrix.mMatrix[5] = newMatrix.mMatrix[5] - pToSubstract.mMatrix[5];
		newMatrix.mMatrix[6] = newMatrix.mMatrix[6] - pToSubstract.mMatrix[6];
		newMatrix.mMatrix[7] = newMatrix.mMatrix[7] - pToSubstract.mMatrix[7];

		newMatrix.mMatrix[8] = newMatrix.mMatrix[8] - pToSubstract.mMatrix[8];
		newMatrix.mMatrix[9] = newMatrix.mMatrix[9] - pToSubstract.mMatrix[9];
		newMatrix.mMatrix[10] = newMatrix.mMatrix[10] - pToSubstract.mMatrix[10];
		newMatrix.mMatrix[11] = newMatrix.mMatrix[11] - pToSubstract.mMatrix[11];

		newMatrix.mMatrix[12] = newMatrix.mMatrix[12] - pToSubstract.mMatrix[12];
		newMatrix.mMatrix[13] = newMatrix.mMatrix[13] - pToSubstract.mMatrix[13];
		newMatrix.mMatrix[14] = newMatrix.mMatrix[14] - pToSubstract.mMatrix[14];
		newMatrix.mMatrix[15] = newMatrix.mMatrix[15] - pToSubstract.mMatrix[15];

		return newMatrix;
	}

	matrix_4 matrix_4::operator*(const matrix_4 &pToMultiply) const
	{
		matrix_4 newMatrix;

		newMatrix.mMatrix[0] = mMatrix[0] * pToMultiply.mMatrix[0] + mMatrix[1] * pToMultiply.mMatrix[4] + mMatrix[2] * pToMultiply.mMatrix[8] + mMatrix[3] *  pToMultiply.mMatrix[12];
		newMatrix.mMatrix[1] = mMatrix[0] * pToMultiply.mMatrix[1] + mMatrix[1] * pToMultiply.mMatrix[5] + mMatrix[2] * pToMultiply.mMatrix[9] + mMatrix[3] *  pToMultiply.mMatrix[13];
		newMatrix.mMatrix[2] = mMatrix[0] * pToMultiply.mMatrix[2] + mMatrix[1] * pToMultiply.mMatrix[6] + mMatrix[2] * pToMultiply.mMatrix[10] + mMatrix[3] * pToMultiply.mMatrix[14];
		newMatrix.mMatrix[3] = mMatrix[0] * pToMultiply.mMatrix[3] + mMatrix[1] * pToMultiply.mMatrix[7] + mMatrix[2] * pToMultiply.mMatrix[11] + mMatrix[3] * pToMultiply.mMatrix[15];
																				  																				
		newMatrix.mMatrix[4] = mMatrix[4] * pToMultiply.mMatrix[0] + mMatrix[5] * pToMultiply.mMatrix[4] + mMatrix[6] * pToMultiply.mMatrix[8] + mMatrix[7] *  pToMultiply.mMatrix[12];
		newMatrix.mMatrix[5] = mMatrix[4] * pToMultiply.mMatrix[1] + mMatrix[5] * pToMultiply.mMatrix[5] + mMatrix[6] * pToMultiply.mMatrix[9] + mMatrix[7] *  pToMultiply.mMatrix[13];
		newMatrix.mMatrix[6] = mMatrix[4] * pToMultiply.mMatrix[2] + mMatrix[5] * pToMultiply.mMatrix[6] + mMatrix[6] * pToMultiply.mMatrix[10] + mMatrix[7] * pToMultiply.mMatrix[14];
		newMatrix.mMatrix[7] = mMatrix[4] * pToMultiply.mMatrix[3] + mMatrix[5] * pToMultiply.mMatrix[7] + mMatrix[6] * pToMultiply.mMatrix[11] + mMatrix[7] * pToMultiply.mMatrix[15];
																				  										
		newMatrix.mMatrix[8] = mMatrix[8] * pToMultiply.mMatrix[0] + mMatrix[9] * pToMultiply.mMatrix[4] + mMatrix[10] * pToMultiply.mMatrix[8] + mMatrix[11] *  pToMultiply.mMatrix[12];
		newMatrix.mMatrix[9] = mMatrix[8] * pToMultiply.mMatrix[1] + mMatrix[9] * pToMultiply.mMatrix[5] + mMatrix[10] * pToMultiply.mMatrix[9] + mMatrix[11] *  pToMultiply.mMatrix[13];
		newMatrix.mMatrix[10]= mMatrix[8] * pToMultiply.mMatrix[2] + mMatrix[9] * pToMultiply.mMatrix[6] + mMatrix[10] * pToMultiply.mMatrix[10] + mMatrix[11] * pToMultiply.mMatrix[14];
		newMatrix.mMatrix[11]= mMatrix[8] * pToMultiply.mMatrix[3] + mMatrix[9] * pToMultiply.mMatrix[7] + mMatrix[10] * pToMultiply.mMatrix[11] + mMatrix[11] * pToMultiply.mMatrix[15];
											
		newMatrix.mMatrix[12] = mMatrix[12] * pToMultiply.mMatrix[0] + mMatrix[13] * pToMultiply.mMatrix[4] + mMatrix[14] * pToMultiply.mMatrix[8] + mMatrix[15] *  pToMultiply.mMatrix[12];
		newMatrix.mMatrix[13] = mMatrix[12] * pToMultiply.mMatrix[1] + mMatrix[13] * pToMultiply.mMatrix[5] + mMatrix[14] * pToMultiply.mMatrix[9] + mMatrix[15] *  pToMultiply.mMatrix[13];
		newMatrix.mMatrix[14] = mMatrix[12] * pToMultiply.mMatrix[2] + mMatrix[13] * pToMultiply.mMatrix[6] + mMatrix[14] * pToMultiply.mMatrix[10] + mMatrix[15] * pToMultiply.mMatrix[14];
		newMatrix.mMatrix[15] = mMatrix[12] * pToMultiply.mMatrix[3] + mMatrix[13] * pToMultiply.mMatrix[7] + mMatrix[14] * pToMultiply.mMatrix[11] + mMatrix[15] * pToMultiply.mMatrix[15];


		return newMatrix;
	}

	//As the divide operation does not exist in matrices, it has to be multiplied with the inverse of the multiplying matrix
	Engine::matrix_4 Engine::matrix_4::operator/(matrix_4 &pToDivide) const
	{
		matrix_4 newMatrix, toDivideInverted;

		toDivideInverted = pToDivide.get_invert();
		
		try
		{
			newMatrix = *this * toDivideInverted;
		}
		catch (const std::exception&)
		{
			return NULL;
		}

		return newMatrix;
	}
}