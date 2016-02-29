/*
 *  Copyright 2010-2016 Fabric Software Inc. All rights reserved.
 */

#ifndef __UI_SCENEHUB_CMD_H__
#define __UI_SCENEHUB_CMD_H__


#include <QtGui/QUndoCommand>
#include <FabricUI/Util/macros.h>

namespace FabricUI
{
  namespace SceneHub
  {
    class SHCmd
    {
      public:
        /// Encodes a rtVal into a Json, saves the rtVal
        /// \param client The core client
        /// \param rtVal The value to encode
        static std::string EncodeRTValToJSON(FabricCore::Client const& client, FabricCore::RTVal const& rtVal);

        /// Decodes a rtVal from a Json, reads the rtVal
        /// \param client The core client
        /// \param rtVal The result value
        /// \param json The string to decode
        static void DecodeRTValFromJSON(FabricCore::Client const& client, FabricCore::RTVal &rtVal, FTL::CStrRef json); 
        
        /// Extracts the name of a command.
        /// \param command The command
        /// \param name The command's name
        static bool ExtractName(const std::string &command, std::string &name);

        /// Extracts the parameters from the command string.
        /// \param command The command
        /// \param params The array of parameters as string
        static bool ExtractParams(const std::string &command, std::vector<std::string> &params);

        /// From the parameter type and its value, creates 
        /// \param client The core client
        /// \param type The parameter type
        /// \param value The parameter value JSon encoded
        static FabricCore::RTVal SetParamValue(FabricCore::Client const& client, std::string const& type, std::string const& value);

        /// Gets the command manager.
        /// \param shObject A reference to SceneHub application
        static FabricCore::RTVal GetCmdManager(FabricCore::RTVal &shObject);

        /// Gets the command at index i of KL stack.
        /// \param client A reference to the fabric client
        /// \param shObject A reference to SceneHub application
        /// \param index The name of the object
        static FabricCore::RTVal RetrieveCmd(FabricCore::Client &client, FabricCore::RTVal &shObject, uint32_t index);

        /// Constructs and executes a command.
        /// \param shObject A reference to SceneHub application
        /// \param cmdName The name of the command
        /// \param cmdDes The command desciprtion
        /// \param params The command parameters
        /// \param exec If true executes the command, just add it to the Qt stack otherwise
        SHCmd(FabricCore::RTVal &shObject,
          const std::string &cmdName, 
          const std::string &cmdDes, 
          std::vector<FabricCore::RTVal> &params, 
          bool exec = true);

        ~SHCmd() {};

        /// Does nothing (don't call the command in KL).
        void doit();
        /// Undoes the command.
        void undo();
        /// Redoes the command.
        void redo();

        /// Gets the command description
        std::string getDesc() const { assert(wasInvoked()); return m_desc; };
        /// Sets the command decription (here the command itself).
        /// \param desc The description
        void setDesc(std::string desc) {m_desc = desc;};

        /// Gets a reference to the sceneHub application. 
        FabricCore::RTVal& getRefOnSCeneHub() { return m_shObject; }

        /// Adds additional dependencies of RTVals to this cmd
        void addRTValDependency(FabricCore::RTVal val);

      protected:
        /// Checks if the command has been already applied.
        bool wasInvoked() const { return m_state != State_New; };

        /// Command states
        enum State {
          State_New,
          State_Done,
          State_Undone,
          State_Redone
        };

        State m_state;
        std::string m_desc;
        unsigned m_coreUndoCount;
        std::vector<FabricCore::RTVal> m_additionalRTVals;

        /// \internal
        /// Refenrece to the sceneHub applcaiton.
        FabricCore::RTVal m_shObject;
    };
  };
};

#endif // __UI_SCENEHUB_CMD_H__
