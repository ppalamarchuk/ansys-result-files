#pragma once

namespace arf {
    namespace inner {
        enum class ResultFileSectionLevel
        {
            BeginLevel,
            GeometryLevel,
            ElementTypeLevel,
            RealConstantsLevel,
            CoordinateSystemLevel,
            NodalCoordinatesLevel,
            ElementsInfoLevel,
            SolutionsLevel,
            DisplacementsLevel,
            ReactionForcesLevel,
            BoundaryConditionsLevel,
            ConstraintsLevel,
            AppliedForcesLevel,
            ElementSolutionLevel
        };

        // An interface class for handling the movement between
        // sections of the result file
        class ResultFileSection
        {
        public:
            virtual ~ResultFileSection() {}
            virtual ResultFileSectionLevel getLevel() const = 0;
        };

        class BeginFileSection : public ResultFileSection
        {
        public:
            ~BeginFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class GeometryFileSection : public ResultFileSection
        {
        public:
            ~GeometryFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class ElementTypeFileSection : public ResultFileSection
        {
        public:
            ~ElementTypeFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class RealConstantsFileSection : public ResultFileSection
        {
        public:
            ~RealConstantsFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class CoordinateSystemFileSection : public ResultFileSection
        {
        public:
            ~CoordinateSystemFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class NodalCoordinatesFileSection : public ResultFileSection
        {
        public:
            ~NodalCoordinatesFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class ElementsInfoFileSection : public ResultFileSection
        {
        public:
            ~ElementsInfoFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class SolutionsFileSection : public ResultFileSection
        {
        public:
            ~SolutionsFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class DisplacementsFileSection : public ResultFileSection
        {
        public:
            ~DisplacementsFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class ReactionForcesFileSection : public ResultFileSection
        {
        public:
            ~ReactionForcesFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class BoundaryConditionsFileSection : public ResultFileSection
        {
        public:
            ~BoundaryConditionsFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class ConstraintsFileSection : public ResultFileSection
        {
        public:
            ~ConstraintsFileSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class AppliedForcesSection : public ResultFileSection
        {
        public:
            ~AppliedForcesSection();
            ResultFileSectionLevel getLevel() const override;
        };

        class ElementSolutionSection : public ResultFileSection
        {
        public:
            ~ElementSolutionSection();
            ResultFileSectionLevel getLevel() const override;
        };
    }
}

