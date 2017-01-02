/*
===========================================================================

Doom 3 BFG Edition GPL Source Code
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company. 

This file is part of the Doom 3 BFG Edition GPL Source Code ("Doom 3 BFG Edition Source Code").  

Doom 3 BFG Edition Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 BFG Edition Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 BFG Edition Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 BFG Edition Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 BFG Edition Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/
#pragma hdrstop
#include "precompiled.h"
#include "../Game_local.h"

enum settingMenuCmds_t
{
	SETTING_CMD_BINDINGS,
};

const static int NUM_SYSTEM_VR_CONTROL_OPTIONS = 8;

float LinearAdjust( const float input, const float currentMin, const float currentMax, const float desiredMin,  float desiredMax );
int	AdjustOption( const int currentValue, const int values[], const int numValues, const int adjustment );

/*
========================
idMenuScreen_Shell_VR_Control_Options::Initialize
========================
*/
void idMenuScreen_Shell_VR_Control_Options::Initialize( idMenuHandler * data ) {
	idMenuScreen::Initialize( data );

	if ( data != NULL ) {
		menuGUI = data->GetGUI();
	}

	SetSpritePath( "menuSystemOptions" );
	
	options = new (TAG_SWF) idMenuWidget_DynamicList();
	options->SetNumVisibleOptions( NUM_SYSTEM_VR_CONTROL_OPTIONS );
	options->SetSpritePath( GetSpritePath(), "info", "options" );
	options->SetWrappingAllowed( true );
	options->SetControlList( true );
	options->Initialize( data );

	btnBack = new (TAG_SWF) idMenuWidget_Button();
	btnBack->Initialize( data );
	btnBack->SetLabel( "VR Options" );
	btnBack->SetSpritePath( GetSpritePath(), "info", "btnBack" );
	btnBack->AddEventAction( WIDGET_EVENT_PRESS ).Set( WIDGET_ACTION_GO_BACK );

	AddChild( options );
	AddChild( btnBack );

	idMenuWidget_ControlButton * control;
			
	control = new (TAG_SWF)idMenuWidget_ControlButton();
	control->SetOptionType( OPTION_SLIDER_TEXT );
	control->SetLabel( "Controller Type" );
	control->SetDataSource( &systemData, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_CONTROLLER_TYPE );
	control->SetupEvents( DEFAULT_REPEAT_TIME, options->GetChildren().Num() );
	control->AddEventAction( WIDGET_EVENT_PRESS ).Set( WIDGET_ACTION_COMMAND, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_CONTROLLER_TYPE );
	options->AddChild( control );

	control = new (TAG_SWF)idMenuWidget_ControlButton();
	control->SetOptionType( OPTION_SLIDER_TEXT );
	control->SetLabel( "Move Mode" );
	control->SetDataSource( &systemData, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_MOVE_MODE );
	control->SetupEvents( DEFAULT_REPEAT_TIME, options->GetChildren().Num() );
	control->AddEventAction( WIDGET_EVENT_PRESS ).Set( WIDGET_ACTION_COMMAND, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_MOVE_MODE );
	options->AddChild( control );

	control = new (TAG_SWF)idMenuWidget_ControlButton();
	control->SetOptionType( OPTION_SLIDER_TEXT );
	control->SetLabel( "Crouch Mode" );
	control->SetDataSource( &systemData, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_CROUCH_MODE );
	control->SetupEvents( DEFAULT_REPEAT_TIME, options->GetChildren().Num() );
	control->AddEventAction( WIDGET_EVENT_PRESS ).Set( WIDGET_ACTION_COMMAND, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_CROUCH_MODE );
	options->AddChild( control );

	control = new (TAG_SWF)idMenuWidget_ControlButton();
	control->SetOptionType( OPTION_SLIDER_TEXT );
	control->SetLabel( "Crouch Trig Dist" );
	control->SetDataSource( &systemData, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_CROUCH_TRIGGER_DIST );
	control->SetupEvents( DEFAULT_REPEAT_TIME, options->GetChildren().Num() );
	control->AddEventAction( WIDGET_EVENT_PRESS ).Set( WIDGET_ACTION_COMMAND, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_CROUCH_TRIGGER_DIST );
	options->AddChild( control );

	control = new (TAG_SWF)idMenuWidget_ControlButton();
	control->SetOptionType( OPTION_SLIDER_TEXT );
	control->SetLabel( "Walk Speed Adj" );
	control->SetDataSource( &systemData, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_WALK_SPEED_ADJUST );
	control->SetupEvents( DEFAULT_REPEAT_TIME, options->GetChildren().Num() );
	control->AddEventAction( WIDGET_EVENT_PRESS ).Set( WIDGET_ACTION_COMMAND, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_WALK_SPEED_ADJUST );
	options->AddChild( control );
	
	control = new (TAG_SWF)idMenuWidget_ControlButton();
	control->SetOptionType( OPTION_SLIDER_TEXT );
	control->SetLabel( "Weapon Pitch" );
	control->SetDataSource( &systemData, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_WEAPON_PITCH );
	control->SetupEvents( DEFAULT_REPEAT_TIME, options->GetChildren().Num() );
	control->AddEventAction( WIDGET_EVENT_PRESS ).Set( WIDGET_ACTION_COMMAND, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_WEAPON_PITCH );
	options->AddChild( control );

	control = new (TAG_SWF)idMenuWidget_ControlButton();
	control->SetOptionType( OPTION_SLIDER_TEXT );
	control->SetLabel( "Flash Pitch" );
	control->SetDataSource( &systemData, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_FLASHLIGHT_PITCH );
	control->SetupEvents( DEFAULT_REPEAT_TIME, options->GetChildren().Num() );
	control->AddEventAction( WIDGET_EVENT_PRESS ).Set( WIDGET_ACTION_COMMAND, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_FLASHLIGHT_PITCH );
	options->AddChild( control );

The of the 	control = new (TAG_SWF)idMenuWidget_ControlButton();
	control->SetOptionType( OPTION_SLIDER_TEXT );
	control->SetLabel( "Talk Mode" );
	control->SetDataSource(&systemData, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_TALK_MODE);
	control->SetupEvents(DEFAULT_REPEAT_TIME, options->GetChildren().Num());
	control->AddEventAction(WIDGET_EVENT_PRESS).Set(WIDGET_ACTION_COMMAND, idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_TALK_MODE);
	options->AddChild(control);

	options->AddEventAction( WIDGET_EVENT_SCROLL_DOWN ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_SCROLL_DOWN_START_REPEATER, WIDGET_EVENT_SCROLL_DOWN ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_UP ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_SCROLL_UP_START_REPEATER, WIDGET_EVENT_SCROLL_UP ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_DOWN_RELEASE ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_STOP_REPEATER, WIDGET_EVENT_SCROLL_DOWN_RELEASE ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_UP_RELEASE ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_STOP_REPEATER, WIDGET_EVENT_SCROLL_UP_RELEASE ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_DOWN_LSTICK ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_SCROLL_DOWN_START_REPEATER, WIDGET_EVENT_SCROLL_DOWN_LSTICK ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_UP_LSTICK ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_SCROLL_UP_START_REPEATER, WIDGET_EVENT_SCROLL_UP_LSTICK ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_DOWN_LSTICK_RELEASE ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_STOP_REPEATER, WIDGET_EVENT_SCROLL_DOWN_LSTICK_RELEASE ) );
	options->AddEventAction( WIDGET_EVENT_SCROLL_UP_LSTICK_RELEASE ).Set( new (TAG_SWF) idWidgetActionHandler( options, WIDGET_ACTION_EVENT_STOP_REPEATER, WIDGET_EVENT_SCROLL_UP_LSTICK_RELEASE ) );
}

/*
========================
idMenuScreen_Shell_VR_Control_Options::Update
========================
*/
void idMenuScreen_Shell_VR_Control_Options::Update() {

	if ( menuData != NULL ) {
		idMenuWidget_CommandBar * cmdBar = menuData->GetCmdBar();
		if ( cmdBar != NULL ) {
			cmdBar->ClearAllButtons();
			idMenuWidget_CommandBar::buttonInfo_t * buttonInfo;			
			buttonInfo = cmdBar->GetButton( idMenuWidget_CommandBar::BUTTON_JOY2 );
			if ( menuData->GetPlatform() != 2 ) {
				buttonInfo->label = "#str_00395";
			}
			buttonInfo->action.Set( WIDGET_ACTION_GO_BACK );

			buttonInfo = cmdBar->GetButton( idMenuWidget_CommandBar::BUTTON_JOY1 );
			buttonInfo->action.Set( WIDGET_ACTION_PRESS_FOCUSED );
		}		
	}

	idSWFScriptObject & root = GetSWFObject()->GetRootObject();
	if ( BindSprite( root ) ) {
		idSWFTextInstance * heading = GetSprite()->GetScriptObject()->GetNestedText( "info", "txtHeading" );
		if ( heading != NULL ) {
			heading->SetText( "VR Control Options" );	
			heading->SetStrokeInfo( true, 0.75f, 1.75f );
		}

		idSWFSpriteInstance * gradient = GetSprite()->GetScriptObject()->GetNestedSprite( "info", "gradient" );
		if ( gradient != NULL && heading != NULL ) {
			gradient->SetXPos( heading->GetTextLength() );
		}
	}

	if ( btnBack != NULL ) {
		btnBack->BindSprite( root );
	}

	idMenuScreen::Update();
}

/*
========================
idMenuScreen_Shell_VR_Control_Options::ShowScreen
========================
*/
void idMenuScreen_Shell_VR_Control_Options::ShowScreen( const mainMenuTransition_t transitionType ) {
	
	systemData.LoadData();
	
	idMenuScreen::ShowScreen( transitionType );
}

/*
========================
idMenuScreen_Shell_VR_Control_Options::HideScreen
========================
*/
void idMenuScreen_Shell_VR_Control_Options::HideScreen( const mainMenuTransition_t transitionType ) {

	if ( systemData.IsRestartRequired() ) {
		class idSWFScriptFunction_Restart : public idSWFScriptFunction_RefCounted {
		public:
			idSWFScriptFunction_Restart( gameDialogMessages_t _msg, bool _restart ) {
				msg = _msg;
				restart = _restart;
			}
			idSWFScriptVar Call( idSWFScriptObject * thisObject, const idSWFParmList & parms ) {
				common->Dialog().ClearDialog( msg );
				if ( restart ) {
					idStr cmdLine = Sys_GetCmdLine();
					if ( cmdLine.Find( "com_skipIntroVideos" ) < 0 ) {
						cmdLine.Append( " +set com_skipIntroVideos 1" );
					}
					Sys_ReLaunch(); // Sys_ReLaunch no longer needs params
				}
				return idSWFScriptVar();
			}
		private:
			gameDialogMessages_t msg;
			bool restart;
		};
		idStaticList<idSWFScriptFunction *, 4> callbacks;
		idStaticList<idStrId, 4> optionText;
		callbacks.Append( new idSWFScriptFunction_Restart( GDM_GAME_RESTART_REQUIRED, false ) );
		callbacks.Append( new idSWFScriptFunction_Restart( GDM_GAME_RESTART_REQUIRED, true ) );
		optionText.Append( idStrId( "#str_00100113" ) ); // Continue
		optionText.Append( idStrId( "#str_02487" ) ); // Restart Now
		common->Dialog().AddDynamicDialog( GDM_GAME_RESTART_REQUIRED, callbacks, optionText, true, idStr() );
	}

	if ( systemData.IsDataChanged() ) {
		systemData.CommitData();
	}

	idMenuScreen::HideScreen( transitionType );
}

/*
========================
idMenuScreen_Shell_VR_Control_Options::HandleAction h
========================
*/
bool idMenuScreen_Shell_VR_Control_Options::HandleAction( idWidgetAction & action, const idWidgetEvent & event, idMenuWidget * widget, bool forceHandled ) {

	if ( menuData == NULL ) {
		return true;
	}
	
	if ( menuData->ActiveScreen() != SHELL_AREA_VR_CONTROL_OPTIONS ) {
		return false;
	}

	widgetAction_t actionType = action.GetType();
	const idSWFParmList & parms = action.GetParms();
	switch ( actionType ) {
		case WIDGET_ACTION_GO_BACK: {
			if ( menuData != NULL ) {
				menuData->SetNextScreen( SHELL_AREA_VR_SETTINGS, MENU_TRANSITION_SIMPLE );
			}
			return true;
		}

		/*
		case WIDGET_ACTION_PRESS_FOCUSED:
			if ( widget->GetDataSourceFieldIndex() == idMenuDataSource_Shell_VR_Control_Options::CONTROL_OPTIONS_FIELD_BINDINGS ) {
				menuData->SetNextScreen( SHELL_AREA_KEYBOARD, MENU_TRANSITION_SIMPLE );
				common->Printf( "Trying to transition\n" );
				return true;
			}
			break; 
		*/

		case WIDGET_ACTION_COMMAND: {

			if ( options == NULL ) {
				return true;
			}

			int selectionIndex = options->GetFocusIndex();
			if ( parms.Num() > 0 ) {
				selectionIndex = parms[0].ToInteger();
			}

			if ( options && selectionIndex != options->GetFocusIndex() ) {
				options->SetViewIndex( options->GetViewOffset() + selectionIndex );
				options->SetFocusIndex( selectionIndex );
			}

			switch ( parms[0].ToInteger() ) {
			case 1: 

				default: {
					systemData.AdjustField( parms[0].ToInteger(), 1 );
					options->Update();
				}
			}

			return true;
		}
		case WIDGET_ACTION_START_REPEATER: {

			if ( options == NULL ) {
				return true;
			}

			if ( parms.Num() == 4 ) {
				int selectionIndex = parms[3].ToInteger();
				if ( selectionIndex != options->GetFocusIndex() ) {
					options->SetViewIndex( options->GetViewOffset() + selectionIndex );
					options->SetFocusIndex( selectionIndex );
				}
			}
			break;
		}
	}

	return idMenuWidget::HandleAction( action, event, widget, forceHandled );
}

/////////////////////////////////
// SCREEN SETTINGS
/////////////////////////////////

/*
========================
idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options
========================
*/
idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options() {
}

/*
========================
idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::LoadData
========================
*/
void idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::LoadData() {

	originalControlType = vr_controllerStandard.GetInteger();
	originalMoveMode = vr_movePoint.GetInteger();
	originalCrouchMode = vr_crouchMode.GetInteger();
	originalCrouchTriggerDistance = vr_crouchTriggerDist.GetFloat();
	originalWalkSpeedAdjust = vr_walkSpeedAdjust.GetFloat();
	originalWeaponPitch = vr_motionWeaponPitchAdj.GetFloat();
	originalFlashPitch = vr_motionFlashPitchAdj.GetFloat();
	originalTalkMode = vr_talkMode.GetInteger();

}

/*
========================
idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::IsRestartRequired
========================
*/
bool idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::IsRestartRequired() const {
	return false;
}

/*
========================
idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::CommitData
========================
*/
void idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::CommitData() {
	cvarSystem->SetModifiedFlags( CVAR_ARCHIVE );
}


/*
========================
idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::AdjustField
========================
*/
void idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::AdjustField( const int fieldIndex, const int adjustAmount ) {
	switch ( fieldIndex )
	{

		case CONTROL_OPTIONS_FIELD_CONTROLLER_TYPE: 
		{
			static const int numValues = 2;
			static const int values[numValues] = { 0, 1 };
			vr_controllerStandard.SetInteger( AdjustOption( vr_controllerStandard.GetInteger(), values, numValues, adjustAmount ) );
			break;
		}

		case CONTROL_OPTIONS_FIELD_MOVE_MODE: 
		{
			static const int numValues = 3;
			static const int values[numValues] = { 0, 1, 2 };
			vr_movePoint.SetInteger( AdjustOption( vr_movePoint.GetInteger(), values, numValues, adjustAmount ) );
			break;
		}

		case CONTROL_OPTIONS_FIELD_CROUCH_MODE: 
		{
			static const int numValues = 2;
			static const int values[numValues] = { 0, 1 };
			vr_crouchMode.SetInteger( AdjustOption( vr_crouchMode.GetInteger(), values, numValues, adjustAmount ) );
			break;
		}

		case CONTROL_OPTIONS_FIELD_CROUCH_TRIGGER_DIST: 
		{
			float td = vr_crouchTriggerDist.GetFloat();
			td += adjustAmount;
			if ( td < 6.0f ) td = 6.0f;
			if ( td > 70 ) td = 70;
			vr_crouchTriggerDist.SetFloat( td );
			break;

		}

		case CONTROL_OPTIONS_FIELD_WALK_SPEED_ADJUST: 
		{
			float ws = vr_walkSpeedAdjust.GetFloat();
			ws += adjustAmount;
			if ( ws < -100 ) ws = -100;
			if ( ws > 150 ) ws = 150;
			vr_walkSpeedAdjust.SetFloat( ws );
			break;
		}
			
		case CONTROL_OPTIONS_FIELD_WEAPON_PITCH: 
		{
			float p = vr_motionWeaponPitchAdj.GetFloat();
			p += adjustAmount;
			if ( p < -100 ) p = -100;
			if ( p > 100 ) p = 100;
			vr_motionWeaponPitchAdj.SetFloat( p );
			break;
		}

		case CONTROL_OPTIONS_FIELD_FLASHLIGHT_PITCH: 
		{
			float p = vr_motionFlashPitchAdj.GetFloat();
			p += adjustAmount;
			if ( p < -100 ) p = -100;
			if ( p > 100 ) p = 100;
			vr_motionFlashPitchAdj.SetFloat( p );
			break;
		}

		case CONTROL_OPTIONS_FIELD_TALK_MODE:
		{
			static const int numValues = 3;
			static const int values[numValues] = { 0, 1, 2 };
			vr_talkMode.SetInteger(AdjustOption(vr_talkMode.GetInteger(), values, numValues, adjustAmount));
			break;
		}

	}
	cvarSystem->ClearModifiedFlags( CVAR_ARCHIVE );
}

/*
========================
idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::GetField	
========================
*/
idSWFScriptVar idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::GetField( const int fieldIndex ) const {
	switch ( fieldIndex )
	{

		case CONTROL_OPTIONS_FIELD_CONTROLLER_TYPE:
			if ( vr_controllerStandard.GetInteger() == 0 )
			{
				return "Motion Controllers";
			}
			else
			{
				return "Standard Controller";
			}

		case CONTROL_OPTIONS_FIELD_MOVE_MODE:
		{
			const int mm = vr_movePoint.GetInteger();

			if ( mm == 1 )
			{
				return "Off Hand = Forward";
			}

			if ( mm == 2 )
			{
				return "Look = forward";
			}

			return "Standard Stick Move";
		}

		case CONTROL_OPTIONS_FIELD_CROUCH_MODE:
			if ( vr_crouchMode.GetInteger() == 0 )
			{
				return "Full Motion Crouching";
			}

			return "Motion Triggered";

		case CONTROL_OPTIONS_FIELD_CROUCH_TRIGGER_DIST:
			return va( "%.0f", vr_crouchTriggerDist.GetFloat() );

		case CONTROL_OPTIONS_FIELD_WALK_SPEED_ADJUST:
			return va( "%.0f", vr_walkSpeedAdjust.GetFloat() );
			
		case CONTROL_OPTIONS_FIELD_WEAPON_PITCH:
			return va( "%.0f", vr_motionWeaponPitchAdj.GetFloat() );

		case CONTROL_OPTIONS_FIELD_FLASHLIGHT_PITCH:
			return va( "%.0f", vr_motionFlashPitchAdj.GetFloat() );

		case CONTROL_OPTIONS_FIELD_TALK_MODE:
			int tm = vr_talkMode.GetInteger();
			if (tm <= 0)
				return "Buttons Only";
			else if (tm >= 2)
				return "Voice Only";
			else
				return "Buttons or Voice";
	}
	return false;
}

/*
========================
idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::IsDataChanged	
========================
*/
bool idMenuScreen_Shell_VR_Control_Options::idMenuDataSource_Shell_VR_Control_Options::IsDataChanged() const {
	
	
	if ( originalControlType != vr_controllerStandard.GetInteger() )
	{
		return true;
	}
	
	if ( originalMoveMode != vr_movePoint.GetInteger() )
	{
		return true;
	}
	
	if ( originalCrouchMode != vr_crouchMode.GetInteger() )
	{
		return true;
	}
	
	if ( originalCrouchTriggerDistance != vr_crouchTriggerDist.GetFloat() )
	{
		return true;
	}
	
	if ( originalWalkSpeedAdjust != vr_walkSpeedAdjust.GetFloat() )
	{
		return true;
	}
		
	if ( originalWeaponPitch != vr_motionWeaponPitchAdj.GetFloat() )
	{
		return true;
	}
	
	if ( originalFlashPitch != vr_motionFlashPitchAdj.GetFloat() )
	{
		return true;
	}
		
	if (originalTalkMode != vr_talkMode.GetInteger())
	{
		return true;
	}

	return false;
}
