#pragma once

#include <algorithm>
#include <string>

#include "../Components/BrickComponent.h"
#include "../Utils/GameConstants.h"
#include "Core/Core.h"
#include "Core/Component/BaseComponent.h"
#include "Core/Component/TextComponent.h"
#include "Core/System/System.h"

class RoundSystem : public System {
public:
    void Init() {
        Signature signature{};
        signature.set(Core::GetCoordinator().GetComponentType<BaseComponent>());
        signature.set(Core::GetCoordinator().GetComponentType<TextComponent>());
        Core::GetCoordinator().SetSystemSignature<RoundSystem>(signature);
    }

    void Reset() {
        winningScore = GetWinningScore();
        currentLevelIndex = 0;
        leftScore = 0;
        rightScore = 0;
        winner = Side::NONE;
        matchOver = false;
        stageCleared = false;
        campaignCompleted = false;
        RefreshHud();
    }

    void StartLevel(const size_t levelIndex) {
        const auto &levelFiles = GetLevelFiles();
        if (levelFiles.empty()) {
            currentLevelIndex = 0;
            stageCleared = true;
            campaignCompleted = true;
            RefreshHud();
            return;
        }

        currentLevelIndex = std::min(levelIndex, levelFiles.size() - 1);
        stageCleared = false;
        campaignCompleted = false;
        RefreshHud();
    }

    bool AwardPoint(const Side side) {
        if (matchOver || (side != Side::LEFT && side != Side::RIGHT)) {
            return matchOver;
        }

        if (side == Side::LEFT) {
            ++leftScore;
        } else {
            ++rightScore;
        }

        if (leftScore >= winningScore) {
            winner = Side::LEFT;
            matchOver = true;
        } else if (rightScore >= winningScore) {
            winner = Side::RIGHT;
            matchOver = true;
        }

        RefreshHud();
        return matchOver;
    }

    bool CheckLevelClear() {
        if (matchOver || stageCleared || HasRemainingObjectiveBricks()) {
            return false;
        }

        stageCleared = true;
        campaignCompleted = currentLevelIndex + 1 >= GetLevelFiles().size();
        RefreshHud();
        return true;
    }

    [[nodiscard]] bool IsMatchOver() const {
        return matchOver;
    }

    [[nodiscard]] bool CanAdvanceLevel() const {
        return stageCleared && !campaignCompleted;
    }

    [[nodiscard]] bool IsCampaignCompleted() const {
        return campaignCompleted;
    }

private:
    size_t currentLevelIndex = 0;
    int leftScore = 0;
    int rightScore = 0;
    int winningScore = DEFAULT_WINNING_SCORE;
    bool matchOver = false;
    bool stageCleared = false;
    bool campaignCompleted = false;
    Side winner = Side::NONE;

    void RefreshHud() {
        UpdateTextEntity(ROUND_LEVEL_ENTITY, BuildLevelText());
        RefreshScoreTexts();
        UpdateTextEntity(ROUND_STATUS_ENTITY, BuildStatusText());
        UpdateTextEntity(ROUND_BANNER_ENTITY, BuildBannerText());
    }

    void RefreshScoreTexts() {
        UpdateTextEntity(PLAYER_LEFT_SCORE_ENTITY, "P1: " + std::to_string(leftScore));
        UpdateTextEntity(PLAYER_RIGHT_SCORE_ENTITY, "P2: " + std::to_string(rightScore));
    }

    std::string BuildStatusText() const {
        if (matchOver) {
            return "ENTER restart  BACKSPACE menu";
        }
        if (stageCleared) {
            return campaignCompleted ? "ENTER restart campaign" : "ENTER next stage";
        }

        return "First to " + std::to_string(winningScore) + " points";
    }

    std::string BuildLevelText() const {
        const auto &levelFiles = GetLevelFiles();
        if (levelFiles.empty()) {
            return "No levels";
        }

        return "Stage " + std::to_string(currentLevelIndex + 1) + "/" + std::to_string(levelFiles.size());
    }

    std::string BuildBannerText() const {
        if (winner == Side::LEFT) {
            return "PLAYER 1 WINS";
        }
        if (winner == Side::RIGHT) {
            return "PLAYER 2 WINS";
        }
        if (stageCleared) {
            return campaignCompleted ? "CAMPAIGN CLEAR" : "STAGE CLEAR";
        }
        return "";
    }

    bool HasRemainingObjectiveBricks() const {
        // The example game keeps progression rules in a custom system so the
        // engine stays generic and reusable across different game types.
        for (const Entity entity : Core::GetCoordinator().GetAllEntities()) {
            if (!Core::GetCoordinator().HasComponent<BaseComponent>(entity) ||
                !Core::GetCoordinator().HasComponent<BrickComponent>(entity)) {
                continue;
            }

            const auto &baseComponent = Core::GetCoordinator().GetComponent<BaseComponent>(entity);
            const auto &brickComponent = Core::GetCoordinator().GetComponent<BrickComponent>(entity);
            if (baseComponent.scene_name == ROUND_SCENE && brickComponent.clearsLevel) {
                return true;
            }
        }

        return false;
    }

    void UpdateTextEntity(const std::string& entityName, const std::string& value) {
        for (const Entity entity : mEntities) {
            auto &baseComponent = Core::GetCoordinator().GetComponent<BaseComponent>(entity);
            if (baseComponent.scene_name != ROUND_SCENE || baseComponent.entity_name != entityName) {
                continue;
            }

            auto &textComponent = Core::GetCoordinator().GetComponent<TextComponent>(entity);
            textComponent.text = value;
            textComponent.dirty = true;
            break;
        }
    }
};
