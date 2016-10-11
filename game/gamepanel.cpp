#include "gamepanel.h"

GamePanel::GamePanel(QWidget *parent) : QWidget(parent)
{
    health_txt.setText("health:");
    health_txt.setAlignment(Qt::AlignRight);
    health_count.setText("--");
    health_count.setAlignment(Qt::AlignLeft);
    weapon_txt.setText("weapon:");
    weapon_txt.setAlignment(Qt::AlignRight);
    weapon_count.setText("pistol");
    weapon_count.setAlignment(Qt::AlignLeft);
    ammunition_txt.setText("ammunition:");
    ammunition_txt.setAlignment(Qt::AlignRight);
    ammunition_count.setText("--");
    ammunition_count.setAlignment(Qt::AlignLeft);
    level_txt.setText("level:");
    level_txt.setAlignment(Qt::AlignRight);
    level_count.setText("--");
    level_count.setAlignment(Qt::AlignLeft);
    score_txt.setText("score:");
    score_txt.setAlignment(Qt::AlignRight);
    score_count.setText("--");
    score_count.setAlignment(Qt::AlignLeft);

    layout.setMargin(0);
    layout.setSpacing(0);
    layout.addWidget(&health_txt);
    layout.addWidget(&health_count);
    layout.addWidget(&weapon_txt);
    layout.addWidget(&weapon_count);
    layout.addWidget(&ammunition_txt);
    layout.addWidget(&ammunition_count);
    layout.addWidget(&level_txt);
    layout.addWidget(&level_count);
    layout.addWidget(&score_txt);
    layout.addWidget(&score_count);
    setLayout(&layout);
    show();
}

void GamePanel::setParam(const DataEngine data)
{
    QString str;
    str.setNum(data.my->getHealth());
    health_count.setText(str);
    str.clear();

    switch(data.my->getWeapon()){
    case PISTOL:
        weapon_count.setText("pistol");
        break;
    case UZI:
        weapon_count.setText("uzi");
        break;
    case ROCKET:
        weapon_count.setText("rocket");
        break;
    case WALL_WEAPON:
        weapon_count.setText("wall");
        break;
    default:
        break;
    }
    BulletBehavior * weapon = *data.my->my_weapon;
    str.setNum(weapon->getAmmunition());
    ammunition_count.setText(str);
    str.clear();
    str.setNum(data.level);
    level_count.setText(str);
    str.clear();
    str.setNum(data.score);
    score_count.setText(str);
    str.clear();
}
