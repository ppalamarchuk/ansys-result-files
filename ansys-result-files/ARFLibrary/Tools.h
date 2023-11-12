#pragma once

#ifdef ARFLIBRARY_EXPORTS
#define ARFLIBRARY_API __declspec(dllexport)
#else
#define ARFLIBRARY_API __declspec(dllimport)
#endif

#include <vector>
#include <array>
#include <memory>

namespace arf {

    class RSTReader;

    namespace structures
    {
        struct ARFLIBRARY_API ResultSetInfo
        {
            int resultSet = -1;             // Selected number of result set
            int numResultSet;               // Number of result sets
            int loadStepNumber;             // load step number
            int substepNumber;              // substep of this load step
            int cumulativeIterationNumber;  // cumulative iteration number
            double time;                    // current solution time
        };

        struct ARFLIBRARY_API ElementType
        {
            int referenceNumber;
            int routineNumber;
            int nodelm;             // number of nodes
            int nodfor;             // number of nodes having nodal forces
            int nodstr;             // number of nodes having nodal stresses
            bool isValid;
        };

        struct ARFLIBRARY_API RealConstant
        {
            int realSetNumber;
            // see ANSYS Elements Reference manual for values for specific element
            std::vector<double> data;
            bool isValid;
        };

        struct ARFLIBRARY_API CoordinateSystem
        {
            int csNumber;
            std::array<double, 9> transformationMatrix;
            std::array<double, 3> origin;                   // XC, YC, ZC
            std::array<double, 2> parameters;               // PAR1, PAR2
            std::array<double, 3> angles;
            double thetaSingularityKey;
            double phiSingulatityKey;
            double type;                                    // 0, 1, 2, or 3
            double referenceNumber;
            bool isValid;
        };

        struct ARFLIBRARY_API NodalCoordinates
        {
            int nodeNumber;
            std::array<double, 3> coordinates;              // X, Y, Z
            std::array<double, 3> rotations;                // THXY, THYZ, THZX
            bool isValid;
        };

        struct ARFLIBRARY_API ElementInfo
        {
            int materialId;                                 // material reference number
            int elementType;                                // element type number
            int realConstantId;                             // real constant reference number
            int sectionNumber;                              // section number;
            int coordSystemId;                              // element coordinate system
            int deathFlag;                                  // 0 - alive, 1 - dead
            int solidModelId;                               // solid model reference
            int shape;                                      // coded shape key
            int elementNumber;                              // element number
            int baseElemId;                                 // base element number
            // node numbers defining the element
            // (See the ANSYS Elements Reference for nodal order of an element)
            std::vector<int> nodes;
            bool isValid;
        };

        struct ARFLIBRARY_API Results1D
        {
            int id;
            std::vector<double> data;
            bool isValid;
        };

        struct ARFLIBRARY_API Results2D
        {
            int id;
            std::vector<std::vector<double>> data;
            bool isValid;
        };
    }

    namespace iterators
    {
        struct ARFLIBRARY_API ElementTypeIterator
        {
            ElementTypeIterator(const ElementTypeIterator& other);
            ElementTypeIterator(int index, int maxIndex = -1, bool read = false);

            structures::ElementType& operator*() const;
            structures::ElementType* operator->();
            ElementTypeIterator& operator++();
            friend bool operator== (const ElementTypeIterator& a, const ElementTypeIterator& b)
            {
                return a.m_currentIndex == b.m_currentIndex;
            }
            friend bool operator!= (const ElementTypeIterator& a, const ElementTypeIterator& b)
            {
                return a.m_currentIndex != b.m_currentIndex;
            }
            void readData();

        private:
            std::unique_ptr<structures::ElementType> m_ptr;
            int m_currentIndex;
            int m_maxIndex;
        };

        struct ARFLIBRARY_API RealConstantIterator
        {
            RealConstantIterator(const RealConstantIterator& other);
            RealConstantIterator(int index, int maxIndex = -1, bool read = false);

            structures::RealConstant& operator*() const;
            structures::RealConstant* operator->();
            RealConstantIterator& operator++();
            friend bool operator== (const RealConstantIterator& a, const RealConstantIterator& b)
            {
                return a.m_currentIndex == b.m_currentIndex;
            }
            friend bool operator!= (const RealConstantIterator& a, const RealConstantIterator& b)
            {
                return a.m_currentIndex != b.m_currentIndex;
            }
            void readData();

        private:
            std::unique_ptr<structures::RealConstant> m_ptr;
            int m_currentIndex;
            int m_maxIndex;
        };

        struct ARFLIBRARY_API CoordinateSystemIterator
        {
            CoordinateSystemIterator(const CoordinateSystemIterator& other);
            CoordinateSystemIterator(int index, int maxIndex = -1, bool read = false);

            structures::CoordinateSystem& operator*() const;
            structures::CoordinateSystem* operator->();
            CoordinateSystemIterator& operator++();
            friend bool operator== (const CoordinateSystemIterator& a, const CoordinateSystemIterator& b)
            {
                return a.m_currentIndex == b.m_currentIndex;
            }
            friend bool operator!= (const CoordinateSystemIterator& a, const CoordinateSystemIterator& b)
            {
                return a.m_currentIndex != b.m_currentIndex;
            }
            void readData();

        private:
            std::unique_ptr<structures::CoordinateSystem> m_ptr;
            int m_currentIndex;
            int m_maxIndex;
        };

        struct ARFLIBRARY_API NodalCoordinatesIterator
        {
            NodalCoordinatesIterator(const NodalCoordinatesIterator& other);
            NodalCoordinatesIterator(int index, int maxIndex = -1, bool read = false);

            structures::NodalCoordinates& operator*() const;
            structures::NodalCoordinates* operator->();
            NodalCoordinatesIterator& operator++();
            friend bool operator== (const NodalCoordinatesIterator& a, const NodalCoordinatesIterator& b)
            {
                return a.m_currentIndex == b.m_currentIndex;
            }
            friend bool operator!= (const NodalCoordinatesIterator& a, const NodalCoordinatesIterator& b)
            {
                return a.m_currentIndex != b.m_currentIndex;
            }
            void readData();

        private:
            std::unique_ptr<structures::NodalCoordinates> m_ptr;
            int m_currentIndex;
            int m_maxIndex;
        };

        struct ARFLIBRARY_API ElementInfoIterator
        {
            ElementInfoIterator(const ElementInfoIterator& other);
            ElementInfoIterator(int index, int maxIndex = -1, bool read = false);

            structures::ElementInfo& operator*() const;
            structures::ElementInfo* operator->();
            ElementInfoIterator& operator++();
            friend bool operator== (const ElementInfoIterator& a, const ElementInfoIterator& b)
            {
                return a.m_currentIndex == b.m_currentIndex;
            }
            friend bool operator!= (const ElementInfoIterator& a, const ElementInfoIterator& b)
            {
                return a.m_currentIndex != b.m_currentIndex;
            }
            void readData();

        private:
            std::unique_ptr<structures::ElementInfo> m_ptr;
            int m_currentIndex;
            int m_maxIndex;
        };

        struct ARFLIBRARY_API Results1DIterator
        {
            enum class Type
            {
                NodalDisplacements,
                ReactionForces,
                Constraints,
                AppliedForces,
                MiscellaneousData,
                ElementForces,
                ElementStresses,
                ElementVolumeAndEnergies,
                ElementFieldGradients,
                ElementElasticStrains,
                ElementPlasticStrains,
                ElementCreepStrains,
                ElementThermalStrains,
                ElementEulerAngles,
                ElementFieldFluxes,
                ElementCoupledFieldForces,
                ElementNonsummableMiscData,
                ElementDensities,
                ElementNonlinearData,
                ElementHeatGeneration,
                ElementTemperatures,
                ElementContactResults,
                ElementSurfaceStresses,
                ElementDiffusionStrains,
                ElementIntegrationPointCoord,
                ElementBackStresses,
                ElementStateVariable,
                MaterialNonlinearRecord,
                ElementTable,
            };

            Results1DIterator(const Results1DIterator& other);
            Results1DIterator(int index, Type type, const std::vector<int>& params, bool read);

            structures::Results1D& operator*() const;
            structures::Results1D* operator->();
            Results1DIterator& operator++();
            friend bool operator== (const Results1DIterator& a, const Results1DIterator& b)
            {
                return a.m_currentIndex == b.m_currentIndex;
            }
            friend bool operator!= (const Results1DIterator& a, const Results1DIterator& b)
            {
                return a.m_currentIndex != b.m_currentIndex;
            }
            void readData();
            void readElementResult(int record);

        private:
            std::unique_ptr<structures::Results1D> m_ptr;
            Type m_type;
            int m_currentIndex;
            std::vector<int> m_params;
        };

        class ARFLIBRARY_API ElementTypeRange
        {
        public:
            ElementTypeRange(RSTReader* container);
            ElementTypeIterator begin() const;
            ElementTypeIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API RealConstantRange
        {
        public:
            RealConstantRange(RSTReader* container);
            RealConstantIterator begin() const;
            RealConstantIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API CoordinateSystemRange
        {
        public:
            CoordinateSystemRange(RSTReader* container);
            CoordinateSystemIterator begin() const;
            CoordinateSystemIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API NodalCoordinatesRange
        {
        public:
            NodalCoordinatesRange(RSTReader* container);
            NodalCoordinatesIterator begin() const;
            NodalCoordinatesIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementInfoRange
        {
        public:
            ElementInfoRange(RSTReader* container);
            ElementInfoIterator begin() const;
            ElementInfoIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API NodalDisplacementsRange
        {
        public:
            NodalDisplacementsRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ReactionForcesRange
        {
        public:
            ReactionForcesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ConstraintsRange
        {
        public:
            ConstraintsRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API AppliedForcesRange
        {
        public:
            AppliedForcesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API MiscellaneousRange
        {
        public:
            MiscellaneousRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementForcesRange
        {
        public:
            ElementForcesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementStressesRange
        {
        public:
            ElementStressesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementVolumeEnergiesRange
        {
        public:
            ElementVolumeEnergiesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementFieldGradientsRange
        {
        public:
            ElementFieldGradientsRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementElasticStrainsRange
        {
        public:
            ElementElasticStrainsRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementPlasticStrainsRange
        {
        public:
            ElementPlasticStrainsRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementCreepStrainsRange
        {
        public:
            ElementCreepStrainsRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementThermalStrainsRange
        {
        public:
            ElementThermalStrainsRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementEulerAnglesRange
        {
        public:
            ElementEulerAnglesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementFieldFluxesRange
        {
        public:
            ElementFieldFluxesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementCoupledFieldForcesRange
        {
        public:
            ElementCoupledFieldForcesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementNonsummableMiscDataRange
        {
        public:
            ElementNonsummableMiscDataRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementDensitiesRange
        {
        public:
            ElementDensitiesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementNonlinearDataRange
        {
        public:
            ElementNonlinearDataRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementHeatGenerationRange
        {
        public:
            ElementHeatGenerationRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementTemperaturesRange
        {
        public:
            ElementTemperaturesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementSurfaceStressesRange
        {
        public:
            ElementSurfaceStressesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementDiffusionStrainsRange
        {
        public:
            ElementDiffusionStrainsRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementTablesRange
        {
        public:
            ElementTablesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementContactResultsRange
        {
        public:
            ElementContactResultsRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementIntPointCoordsRange
        {
        public:
            ElementIntPointCoordsRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementBackStressesRange
        {
        public:
            ElementBackStressesRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API ElementStateVariableRange
        {
        public:
            ElementStateVariableRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };

        class ARFLIBRARY_API MaterialsNonlinearRange
        {
        public:
            MaterialsNonlinearRange(RSTReader* container);
            Results1DIterator begin() const;
            Results1DIterator end() const;
        private:
            RSTReader* m_container;
        };
    }
}

