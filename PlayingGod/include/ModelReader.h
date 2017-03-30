////////////////////////////////////////////////////////////
//
// Playing God (3D Procedural World Generation) - Created by Jegor Kharlamov
// Created for Personal Final Year Project Year 3 at De Montfort University - Games Programming Course
//
// Playing God is a 3D world exploration game where the player can operate 
// a computer which generates new worlds based on selected parameters and creates a portal to them.
// The player can then travel through the portal to explore the worlds and search
// for powercells around the procedurally generated maps.
//
////////////////////////////////////////////////////////////
#pragma once

#include "PreHeader.h"

using namespace std;

class ModelReader
{
	private:
		
		static const int forwardSlash = 0x2F; // Forward slash

		// For storing read data from the obj file

		vector<float> m_vertices; ///< vector of verticies
		vector<float> m_vertexNormals; ///< vector of vertex normals
		vector<float> m_vertexTextureCoordinates; ///< vector of UV coordinates

		vector<unsigned int> m_faceVertexIndices; ///< Face vertex index used to create vertex triplets
		vector<unsigned int> m_faceTextureIndices;  ///< Face texture Index used to create UV pairs
		vector<unsigned int> m_faceNormalIndices;  ///< Vertex normal index used to create vertex normal triplets

		string m_modelName; ///< String representing the name of model

		vector<float> m_vertexTriplets;	///< vector of a set of model verticies 
		vector<float> m_vertexNormalTriplets;  ///< vector of a set of model vertex normals
		vector<float> m_vertexTexturePairs; ///< vector of a set of model UV coordinates

	public:
		////////////////////////////////////////////////////////////
		/// \brief Overloaded constructer which takes a .obj file location and gets a vector if its vertices, normals and UV coordinates
		///
		/// \param filename location of .obj file
		/// \see m_vertexTriplets
		/// \see m_vertexNormalTriplets
		/// \see m_vertexTexturePairs
		///
		////////////////////////////////////////////////////////////
		ModelReader(string filename);
		~ModelReader(void);

		////////////////////////////////////////////////////////////
		/// \brief Reads .obj file and retrives important infomation for model loading
		///
		/// \param filename location of .obj file
		/// \see m_vertexTriplets
		/// \see m_vertexNormalTriplets
		/// \see m_vertexTexturePairs
		///
		////////////////////////////////////////////////////////////
		void ModelReader::ReadModelObjData(string filename);

		////////////////////////////////////////////////////////////
		/// \brief Gets all 3 verticies from a line starting with a "v" and pushes them onto m_verticies
		///
		/// \param iss used for processing file data
		/// \see m_vertices
		/// 
		/// 
		///
		////////////////////////////////////////////////////////////
		void ProcessVertexLine(istringstream& iss);

		////////////////////////////////////////////////////////////
		/// \brief Gets all 3 verticies normals from a line starting with a "vn" and pushes them onto m_vertexNormals
		///
		/// \param iss used for processing file data
		/// \see m_vertexNormals
		/// 
		/// 
		///
		////////////////////////////////////////////////////////////
		void ProcessVertexNormalLine(istringstream& iss);

		////////////////////////////////////////////////////////////
		/// \brief Gets all 2 UV normals from a line starting with a "vt" and pushes them onto m_vertexTextureCoordinates
		///
		/// \param iss used for processing file data
		/// \see m_vertexTextureCoordinates
		/// 
		/// 
		///
		////////////////////////////////////////////////////////////
		void ProcessVertexTextureLine(istringstream& iss);

		////////////////////////////////////////////////////////////
		/// \brief Gets face lines for texturing and push back onto m_faceNormalIndices
		///
		/// \param iss used for processing file data
		/// \see m_faceNormalIndices
		////////////////////////////////////////////////////////////
		void ProcessFaceLine(istringstream& iss);

		////////////////////////////////////////////////////////////
		/// \brief Creates vertex triplets from previously acquired verticies
		///
		/// \see m_vertexTriplets
		/// \see m_vertices
		////////////////////////////////////////////////////////////
		void CreateExpandedVertices();

		////////////////////////////////////////////////////////////
		/// \brief Creates vertex normal triplets from previously acquired verticies
		///
		/// \see m_vertexNormalTriplets
		/// \see m_vertexNormals
		////////////////////////////////////////////////////////////
		void CreateExpandedNormals();

		////////////////////////////////////////////////////////////
		/// \brief Creates face texture pairs from previously acquired verticies
		///
		/// \see m_faceTextureIndices
		/// \see m_vertexTexturePairs
		////////////////////////////////////////////////////////////
		void CreateExpandedTextureCoordinates();


		////////////////////////////////////////////////////////////
		/// \brief Returns vertex coordinates of model
		///
		/// \return m_vertexTriplets
		////////////////////////////////////////////////////////////
		vector<float>& GetVertices();

		////////////////////////////////////////////////////////////
		/// \brief Returns Normal coordinates of model
		///
		/// \return m_vertexNormalTriplets
		////////////////////////////////////////////////////////////
		vector<float>& GetNormals();

		////////////////////////////////////////////////////////////
		/// \brief Returns face texture pairs of model
		///
		/// \return m_vertexTexturePairs
		////////////////////////////////////////////////////////////
		vector<float>& GetTextureCoordinates();

};

////////////////////////////////////////////////////////////
/// \class ModelReader
///
/// The purpose of this class is to read a .obj file and 
/// get its verticies, normals and texture UV coordinates.
/// This data can then be used by other classes to render the
/// models within the world.
/// 
/// To initilise a ModelLoader all that needs to be done is
/// to run the constructor with a filename which is a path to a .obj
////////////////////////////////////////////////////////////