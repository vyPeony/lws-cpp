using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lws_form
{
    public class Enchantment
    {
        public Enchantment(int id, string name)
        {
            ID = id;
            Name = name;
        }
        public int ID;
        public string Name;
    }

    public class Const
    {
        public static Enchantment[] EnchantmentList =
        {
            new Enchantment(10000,"～～を上げる"),
            new Enchantment(20000,"～～への耐性を授ける"),
            new Enchantment(30000,"～～の技能を上げる"),
            new Enchantment(60000,"～～を維持する"),
            new Enchantment(70000,"～～属性の追加ダメージを与える"),
            new Enchantment(00000,"その他"),
        };

        public static Enchantment[] EnchantmentDetailList_1 =
        {
            new Enchantment(10010,"筋力を上げる"),
            new Enchantment(10011,"耐久を上げる"),
            new Enchantment(10012,"器用を上げる"),
            new Enchantment(10013,"感覚を上げる"),
            new Enchantment(10014,"意思を上げる"),
            new Enchantment(10015,"習得を上げる"),
            new Enchantment(10016,"魔力を上げる"),
            new Enchantment(10017,"魅力を上げる"),
            new Enchantment(10018,"速度を上げる"),
            new Enchantment(10019,"運勢を上げる"),
        };

        public static Enchantment[] EnchantmentDetailList_2 =
        {
            new Enchantment(20050,"火炎への耐性を授ける"),
            new Enchantment(20051,"冷気への耐性を授ける"),
            new Enchantment(20052,"電撃への耐性を授ける"),
            new Enchantment(20053,"暗黒への耐性を授ける"),
            new Enchantment(20054,"幻惑への耐性を授ける"),
            new Enchantment(20055,"毒への耐性を授ける"),
            new Enchantment(20056,"地獄への耐性を授ける"),
            new Enchantment(20057,"音への耐性を授ける"),
            new Enchantment(20058,"神経への耐性を授ける"),
            new Enchantment(20059,"混沌への耐性を授ける"),
            new Enchantment(20060,"魔法への耐性を授ける"),
        };

        public static Enchantment[] EnchantmentDetailList_3 =
{
            new Enchantment(30150,"読書の技能を上げる"),
            new Enchantment(30151,"遺伝子学の技能を上げる"),
            new Enchantment(30152,"戦術の技能を上げる"),
            new Enchantment(30153,"重量挙げの技能を上げる"),
            new Enchantment(30154,"治癒の技能を上げる"),
            new Enchantment(30155,"瞑想の技能を上げる"),
            new Enchantment(30156,"交渉の技能を上げる"),
            new Enchantment(30157,"隠密の技能を上げる"),
            new Enchantment(30158,"鍵開けの技能を上げる"),
            new Enchantment(30159,"探知の技能を上げる"),
            new Enchantment(30160,"投資の技能を上げる"),
            new Enchantment(30161,"解剖学の技能を上げる"),
            new Enchantment(30162,"自然鑑定の技能を上げる"),
            new Enchantment(30163,"採掘の技能を上げる"),
            new Enchantment(30164,"魔力の限界の技能を上げる"),
            new Enchantment(30165,"暗記の技能を上げる"),
            new Enchantment(30166,"二刀流の技能を上げる"),
            new Enchantment(30167,"両手持ちの技能を上げる"),
            new Enchantment(30168,"盾の技能を上げる"),
            new Enchantment(30169,"重装備の技能を上げる"),
            new Enchantment(30170,"中装備の技能を上げる"),
            new Enchantment(30171,"軽装備の技能を上げる"),
            new Enchantment(30172,"詠唱の技能を上げる"),
            new Enchantment(30173,"回避の技能を上げる"),
            new Enchantment(30174,"魔道具の技能を上げる"),
            new Enchantment(30175,"罠解体の技能を上げる"),
            new Enchantment(30176,"大工の技能を上げる"),
            new Enchantment(30177,"裁縫の技能を上げる"),
            new Enchantment(30178,"錬金術の技能を上げる"),
            new Enchantment(30179,"宝石細工の技能を上げる"),
            new Enchantment(30180,"栽培の技能を上げる"),
            new Enchantment(30181,"信仰の技能を上げる"),
            new Enchantment(30182,"旅歩きの技能を上げる"),
            new Enchantment(30183,"演奏の技能を上げる"),
            new Enchantment(30184,"料理の技能を上げる"),
            new Enchantment(30185,"釣りの技能を上げる"),
            new Enchantment(30186,"心眼の技能を上げる"),
            new Enchantment(30187,"見切りの技能を上げる"),
            new Enchantment(30188,"魔力制御の技能を上げる"),
            new Enchantment(30189,"射撃の技能を上げる"),
        };

        public static Enchantment[] EnchantmentDetailList_4 =
{
            new Enchantment(60010,"筋力を維持する"),
            new Enchantment(60011,"耐久を維持する"),
            new Enchantment(60012,"器用を維持する"),
            new Enchantment(60013,"感覚を維持する"),
            new Enchantment(60014,"意思を維持する"),
            new Enchantment(60015,"習得を維持する"),
            new Enchantment(60016,"魔力を維持する"),
            new Enchantment(60017,"魅力を維持する"),
            new Enchantment(60018,"速度を維持する"),
            new Enchantment(60019,"運勢を維持する"),
        };

        public static Enchantment[] EnchantmentDetailList_5 =
{
            new Enchantment(70050,"火炎属性の追加ダメージを与える"),
            new Enchantment(70051,"冷気属性の追加ダメージを与える"),
            new Enchantment(70052,"電撃属性の追加ダメージを与える"),
            new Enchantment(70053,"暗黒属性の追加ダメージを与える"),
            new Enchantment(70054,"幻惑属性の追加ダメージを与える"),
            new Enchantment(70055,"毒属性の追加ダメージを与える"),
            new Enchantment(70056,"地獄属性の追加ダメージを与える"),
            new Enchantment(70057,"音属性の追加ダメージを与える"),
            new Enchantment(70058,"神経属性の追加ダメージを与える"),
            new Enchantment(70059,"混沌属性の追加ダメージを与える"),
            new Enchantment(70060,"魔法属性の追加ダメージを与える"),
        };

        public static Enchantment[] EnchantmentDetailList_Extra =
        {
            new Enchantment(21,"ランダムなテレポートを引き起こす"),
            new Enchantment(22,"テレポートを妨害する"),
            new Enchantment(23,"盲目を無効にする"),
            new Enchantment(24,"麻痺を無効にする"),
            new Enchantment(25,"混乱を無効にする"),
            new Enchantment(26,"恐怖を無効にする"),
            new Enchantment(27,"睡眠を無効にする"),
            new Enchantment(28,"毒を無効にする"),
            new Enchantment(29,"速度を上げ、ワールドマップでの移動時間を短くする"),
            new Enchantment(30,"エーテルの風からあなたを保護する"),
            new Enchantment(31,"雷雨と雪による足止めを無効にする"),
            new Enchantment(32,"あなたを浮遊させる"),
            new Enchantment(33,"あなたを変異から保護する"),
            new Enchantment(34,"魔法の威力を高める"),
            new Enchantment(35,"透明な存在を見ることを可能にする"),
            new Enchantment(36,"攻撃対象からスタミナを吸収する"),
            new Enchantment(37,"全てを終結させる"),
            new Enchantment(38,"攻撃対象からマナを吸収する"),
            new Enchantment(39,"完全貫通攻撃発動の機会を増やす"),
            new Enchantment(40,"稀に時を止める"),
            new Enchantment(41,"アイテムを盗まれなくする"),
            new Enchantment(42,"腐ったものを難なく消化させる"),
            new Enchantment(43,"呪いの言葉から保護する"),
            new Enchantment(44,"クリティカルヒットの機会を増やす"),
            new Enchantment(45,"使用者の生き血を吸う"),
            new Enchantment(46,"あなたの成長を妨げる"),
            new Enchantment(47,"魔物を呼び寄せる"),
            new Enchantment(48,"異物の体内への侵入を防ぐ"),
            new Enchantment(49,"演奏報酬の品質を上げる"),
            new Enchantment(50,"追加打撃の機会を増やす"),
            new Enchantment(51,"追加射撃の機会を増やす"),
            new Enchantment(52,"被る物理ダメージを軽減する"),
            new Enchantment(53,"被るダメージを稀に無効にする"),
            new Enchantment(54,"攻撃された時、相手に切り傷のダメージを与える"),
            new Enchantment(55,"出血を抑える"),
            new Enchantment(56,"神が発する電波をキャッチする"),
            new Enchantment(57,"竜族に対して強力な威力を発揮する"),
            new Enchantment(58,"不死者に対して強力な威力を発揮する"),
            new Enchantment(59,"他者の信仰を明らかにする"),
            new Enchantment(60,"深い音色で聴衆を酔わす"),
            new Enchantment(61,"神に対して強力な威力を発揮する")
        };
    }
}
