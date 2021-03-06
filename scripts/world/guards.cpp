/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Guards
SD%Complete: 100
SDComment: CombatAI should be organized better for future.
SDCategory: Guards
EndScriptData */

/* ContentData
guard_azuremyst
guard_bluffwatcher
guard_contested
guard_darnassus
guard_dunmorogh
guard_durotar
guard_elwynnforest
guard_eversong
guard_exodar
guard_ironforge
guard_mulgore
guard_orgrimmar
guard_shattrath
guard_shattrath_aldor
guard_shattrath_scryer
guard_silvermoon
guard_stormwind
guard_teldrassil
guard_tirisfal
guard_undercity
EndContentData */

#include "precompiled.h"
#include "guard_ai.h"

CreatureAI* GetAI_guard_azuremyst(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_bluffwatcher(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_contested(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_darnassus(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_dunmorogh(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_durotar(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_elwynnforest(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_eversong(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_exodar(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_ironforge(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_mulgore(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_orgrimmar(Creature* pCreature)
{
    return new guardAI_orgrimmar(pCreature);
}

CreatureAI* GetAI_guard_shattrath(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_shattrath_aldor
 *******************************************************/

struct MANGOS_DLL_DECL guard_shattrath_aldorAI : public guardAI
{
    guard_shattrath_aldorAI(Creature* pCreature) : guardAI(pCreature) { Reset(); }

    uint32 m_uiExile_Timer;
    uint32 m_uiBanish_Timer;
    ObjectGuid m_playerGuid;
    bool m_bCanTeleport;

    void Reset()
    {
        m_uiBanish_Timer = 5000;
        m_uiExile_Timer = 8500;
        m_playerGuid.Clear();
        m_bCanTeleport = false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bCanTeleport)
        {
            if (m_uiExile_Timer < uiDiff)
            {
                if (Player* pTarget = m_creature->GetMap()->GetPlayer(m_playerGuid))
                {
                    pTarget->CastSpell(pTarget, SPELL_EXILE, true);
                    pTarget->CastSpell(pTarget, SPELL_BANISH_TELEPORT, true);
                }

                m_playerGuid.Clear();
                m_uiExile_Timer = 8500;
                m_bCanTeleport = false;
            }
            else
                m_uiExile_Timer -= uiDiff;
        }
        else if (m_uiBanish_Timer < uiDiff)
        {
            Unit* pVictim = m_creature->getVictim();

            if (pVictim && pVictim->GetTypeId() == TYPEID_PLAYER)
            {
                DoCastSpellIfCan(pVictim, SPELL_BANISHED_SHATTRATH_A);
                m_uiBanish_Timer = 9000;
                m_playerGuid = pVictim->GetObjectGuid();
                m_bCanTeleport = true;
            }
        }
        else
            m_uiBanish_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_guard_shattrath_aldor(Creature* pCreature)
{
    return new guard_shattrath_aldorAI(pCreature);
}

/*******************************************************
 * guard_shattrath_scryer
 *******************************************************/

struct MANGOS_DLL_DECL guard_shattrath_scryerAI : public guardAI
{
    guard_shattrath_scryerAI(Creature* pCreature) : guardAI(pCreature) { Reset(); }

    uint32 m_uiExile_Timer;
    uint32 m_uiBanish_Timer;
    ObjectGuid m_playerGuid;
    bool m_bCanTeleport;

    void Reset()
    {
        m_uiBanish_Timer = 5000;
        m_uiExile_Timer = 8500;
        m_playerGuid.Clear();
        m_bCanTeleport = false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bCanTeleport)
        {
            if (m_uiExile_Timer < uiDiff)
            {
                if (Player* pTarget = m_creature->GetMap()->GetPlayer(m_playerGuid))
                {
                    pTarget->CastSpell(pTarget, SPELL_EXILE, true);
                    pTarget->CastSpell(pTarget, SPELL_BANISH_TELEPORT, true);
                }

                m_playerGuid.Clear();
                m_uiExile_Timer = 8500;
                m_bCanTeleport = false;
            }
            else
                m_uiExile_Timer -= uiDiff;
        }
        else if (m_uiBanish_Timer < uiDiff)
        {
            Unit* pVictim = m_creature->getVictim();

            if (pVictim && pVictim->GetTypeId() == TYPEID_PLAYER)
            {
                DoCastSpellIfCan(pVictim, SPELL_BANISHED_SHATTRATH_S);
                m_uiBanish_Timer = 9000;
                m_playerGuid = pVictim->GetObjectGuid();
                m_bCanTeleport = true;
            }
        }
        else
            m_uiBanish_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_guard_shattrath_scryer(Creature* pCreature)
{
    return new guard_shattrath_scryerAI(pCreature);
}

CreatureAI* GetAI_guard_silvermoon(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_stormwind(Creature* pCreature)
{
    return new guardAI_stormwind(pCreature);
}

CreatureAI* GetAI_guard_teldrassil(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_tirisfal(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_undercity(Creature* pCreature)
{
    return new guardAI(pCreature);
}

// GUARD ANTI PVP
struct MANGOS_DLL_DECL guardAI_antipvp : public ScriptedAI
{
    uint32 CheckTimer;
    bool IsAttacking;

    guardAI_antipvp(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

        void Reset()
        {
                m_creature->RemoveAllAuras();
                m_creature->DeleteThreatList();
                m_creature->CombatStop(true);
                m_creature->GetMotionMaster()->MoveTargetedHome();
                IsAttacking = false;
        }

        void CheckUnit(Unit* who)
        {

                //sLog.outDebug("ANTIPVP : Checkunit %s", who->GetName());

                // test for a player
                if(who->GetTypeId() != TYPEID_PLAYER)return;

                // ATTACK_DISTANCE = 5.0f
                if (!m_creature->IsWithinDistInMap(who, 10.0f))return;

                if (!m_creature->getVictim())
                {
                        if(who->isAttackingPlayer() && who->getVictim() != NULL && who->getVictim()->GetTypeId() == TYPEID_PLAYER)
                        {
                                 sLog.outDebug("ANTIPVP : %s is in combat with %s : adding threat", who->GetName(), who->getVictim()->GetName());

                                m_creature->AddThreat(who, 1.0f);
                                AttackStart(who);
                                IsAttacking = true;
                        }
                }
        }

    void UpdateAI(const uint32 diff)
    {
                if (CheckTimer < diff)
                {
                        //sLog.outDebug("ANTIPVP : Checktimer");
                        // find all units at 10 points around
                        Map::PlayerList const &PlList =  m_creature->GetMap()->GetPlayers();
                        if (!PlList.isEmpty())
                        {
                                for(Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                                {
                                        if (Player* pPlayer = i->getSource())
                                        {
                                                if (pPlayer->isGameMaster())
                                                        continue;

                                                if (!pPlayer->isAlive())
                                                        continue;

                                                CheckUnit(pPlayer);
                                        }
                                }
                        }

                        CheckTimer = 1000;
                }
                else CheckTimer -= diff;

                if (m_creature->getVictim())
                {
                        //sLog.outDebug("ANTIPVP : Have vicitm : do melee attack");
                        DoMeleeAttackIfReady();
                }
                else if (IsAttacking)
                {
                        Reset();
                }

    }
};

/*******************************************************
 * guard_antipvp
 *******************************************************/
CreatureAI* GetAI_guard_antipvp(Creature* pCreature)
{
    return new guardAI_antipvp(pCreature);
}


void AddSC_guards()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "guard_azuremyst";
    pNewScript->GetAI = &GetAI_guard_azuremyst;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_bluffwatcher";
    pNewScript->GetAI = &GetAI_guard_bluffwatcher;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_contested";
    pNewScript->GetAI = &GetAI_guard_contested;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_darnassus";
    pNewScript->GetAI = &GetAI_guard_darnassus;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_dunmorogh";
    pNewScript->GetAI = &GetAI_guard_dunmorogh;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_durotar";
    pNewScript->GetAI = &GetAI_guard_durotar;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_elwynnforest";
    pNewScript->GetAI = &GetAI_guard_elwynnforest;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_eversong";
    pNewScript->GetAI = &GetAI_guard_eversong;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_exodar";
    pNewScript->GetAI = &GetAI_guard_exodar;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_ironforge";
    pNewScript->GetAI = &GetAI_guard_ironforge;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_mulgore";
    pNewScript->GetAI = &GetAI_guard_mulgore;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_orgrimmar";
    pNewScript->GetAI = &GetAI_guard_orgrimmar;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_shattrath";
    pNewScript->GetAI = &GetAI_guard_shattrath;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_shattrath_aldor";
    pNewScript->GetAI = &GetAI_guard_shattrath_aldor;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_shattrath_scryer";
    pNewScript->GetAI = &GetAI_guard_shattrath_scryer;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_silvermoon";
    pNewScript->GetAI = &GetAI_guard_silvermoon;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_stormwind";
    pNewScript->GetAI = &GetAI_guard_stormwind;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_teldrassil";
    pNewScript->GetAI = &GetAI_guard_teldrassil;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_tirisfal";
    pNewScript->GetAI = &GetAI_guard_tirisfal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_undercity";
    pNewScript->GetAI = &GetAI_guard_undercity;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "guard_antipvp";
    pNewScript->GetAI = &GetAI_guard_antipvp;
    pNewScript->RegisterSelf();
}
