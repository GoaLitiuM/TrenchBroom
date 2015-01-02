/*
 Copyright (C) 2010-2014 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TrenchBroom__World__
#define __TrenchBroom__World__

#include "TrenchBroom.h"
#include "VecMath.h"
#include "Model/AttributableNode.h"
#include "Model/AttributableNodeIndex.h"
#include "Model/IssueGeneratorRegistry.h"
#include "Model/MapFormat.h"
#include "Model/ModelFactory.h"
#include "Model/ModelFactoryImpl.h"
#include "Model/Node.h"
#include "Model/Picker.h"

namespace TrenchBroom {
    namespace Model {
        class BrushContentTypeBuilder;
        class PickResult;
        
        class World : public AttributableNode, public ModelFactory {
        private:
            ModelFactoryImpl m_factory;
            Layer* m_defaultLayer;
            Picker m_picker;
            AttributableNodeIndex m_attributableIndex;
            IssueGeneratorRegistry m_issueGeneratorRegistry;
        public:
            World(MapFormat::Type mapFormat, const BrushContentTypeBuilder* brushContentTypeBuilder);
        public: // layer management
            Layer* defaultLayer() const;
            LayerList allLayers() const;
            LayerList customLayers() const;
        private:
            void createDefaultLayer();
        public: // selection
            // issue generator registration
            void registerIssueGenerators(const IssueGeneratorList& generators);
            void unregisterAllIssueGenerators();
        private:
            void updateAllIssues();
        public: // picking
            void pick(const Ray3& ray, PickResult& pickResult) const;
        private: // implement Node interface
            Node* doClone(const BBox3& worldBounds) const;
            bool doCanAddChild(const Node* child) const;
            bool doCanRemoveChild(const Node* child) const;
            bool doRemoveIfEmpty() const;
            void doDescendantWasAdded(Node* node);
            void doDescendantWasRemoved(Node* node);
            void doDescendantWillChange(Node* node);
            void doDescendantDidChange(Node* node);
            bool doSelectable() const;
            void doUpdateIssues(Node* node);
            void doAccept(NodeVisitor& visitor);
            void doAccept(ConstNodeVisitor& visitor) const;
            void doFindAttributableNodesWithAttribute(const AttributeName& name, const AttributeValue& value, AttributableNodeList& result) const;
            void doFindAttributableNodesWithNumberedAttribute(const AttributeName& prefix, const AttributeValue& value, AttributableNodeList& result) const;
            void doAddToIndex(AttributableNode* attributable, const AttributeName& name, const AttributeValue& value);
            void doRemoveFromIndex(AttributableNode* attributable, const AttributeName& name, const AttributeValue& value);
        private: // implement AttributableNode interface
            void doAttributesDidChange();
            bool doIsAttributeNameMutable(const AttributeName& name) const;
            bool doIsAttributeValueMutable(const AttributeName& name) const;
        private: // implement ModelFactory interface
            MapFormat::Type doGetFormat() const;
            World* doCreateWorld() const;
            Layer* doCreateLayer(const String& name) const;
            Group* doCreateGroup(const String& name) const;
            Entity* doCreateEntity() const;
            Brush* doCreateBrush(const BBox3& worldBounds, const BrushFaceList& faces) const;
            BrushFace* doCreateFace(const Vec3& point1, const Vec3& point2, const Vec3& point3, const String& textureName) const;
            BrushFace* doCreateFace(const Vec3& point1, const Vec3& point2, const Vec3& point3, const String& textureName, const Vec3& texAxisX, const Vec3& texAxisY) const;
        private:
            World(const World&);
            World& operator=(const World&);
        };
    }
}

#endif /* defined(__TrenchBroom__World__) */
