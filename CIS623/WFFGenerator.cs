using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WFF
{
    enum PropType
    {
        Atom = 0,
        Not = 1,
        And = 2,
        Imply = 3
    }

    class WFFGenerator
    {
        public WFFGenerator(int nCount)
        {
            nodeCount = nCount;
            formulaCount = 10;

            terms = new List<Atom>() 
            {
                new Atom(){Name = "A", Value = true},
                new Atom(){Name = "B", Value = true},
                new Atom(){Name = "C", Value = true},
                new Atom(){Name = "D", Value = true}
            };

            formulas = new Dictionary<string, Formula>(formulaCount);
        }

        public IDictionary<string, Formula> GetWellFormedFormulas()
        {
            while (formulas.Count < 10) GenerateWFF();
            return formulas;
        }

        private void GenerateWFF()
        {
            ParseNode root = null;
            Formula form = new Formula();
            IList<ParseNode> nodes = GenerateLeafNodes();
            //the number of nodes, which are predicate "NOT", required in formula
            int notCount = (nodeCount - 2 * nodes.Count + 1);
            int rndMin = 2;

            //if list contain more than 1 nodes, the formula is not generated
            while (nodes.Count > 1)
            {
                rndMin = notCount > 0 ? 1 : 2;
                ParseNode node = new ParseNode((PropType)rnd.Next(rndMin, 4));

                if (node.Type == PropType.Not)
                {
                    int index = rnd.Next(nodes.Count / 2);
                    node[0] = nodes[index];
                    nodes[index] = node;
                    --notCount;
                }
                else
                {
                    node[0] = nodes[nodes.Count - 2];
                    node[1] = nodes[nodes.Count - 1];
                    nodes.RemoveAt(nodes.Count - 1);
                    nodes.RemoveAt(nodes.Count - 1);
                    nodes.Add(node);
                }

            }

            root = nodes[0];

            while (notCount > 0)
            {
                ParseNode node = new ParseNode(PropType.Not);
                node[0] = root;
                root = node;
                --notCount;
            }


            form.ParseTree = root;
            if (formulas.ContainsKey(form.ToString()) || !IsWellFormed(form)) return;

            formulas.Add(new KeyValuePair<string, Formula>(form.ToString(), form));
        }

        private IList<ParseNode> GenerateLeafNodes()
        {
            int atomCount = Convert.ToInt32(nodeCount / 2.1);
            IList<ParseNode> leafs = new List<ParseNode>(atomCount);
            IList<int> each = new List<int>(terms.Count);
            int count = -1;
            while (++count < terms.Count)
                each.Add(count);

            //add each term at least once
            while (each.Count != 0)
            {
                ParseNode node = new ParseNode(PropType.Atom);
                int index = each[rnd.Next(each.Count)];
                each.Remove(index);
                node.Atom = terms[index];
                leafs.Add(node);
            }

            while (leafs.Count < atomCount)
            {
                ParseNode node = new ParseNode(PropType.Atom);
                int index = rnd.Next(terms.Count);
                node.Atom = terms[index];
                leafs.Add(node);
            }

            return leafs;
        }

        public bool IsWellFormed(Formula form, int level = 0)
        {
            if (level == terms.Count) return form.Value;

            terms[level].Value = false;
            if (!IsWellFormed(form, level + 1)) return false;

            terms[level].Value = true;
            return IsWellFormed(form, level + 1);
        }

        public int Count { get { return nodeCount; } }

        private readonly int formulaCount;
        private readonly int nodeCount;
        private IList<Atom> terms;
        private IDictionary<string, Formula> formulas;
        Random rnd = new Random();
    }

    class Atom
    {
        public string Name { get; set; }
        public bool Value { get; set; }
    }


    class Formula
    {
        #region Functions

        public override string ToString()
        {
            if (tree == null) return null;
            if (string.IsNullOrEmpty(formula))
            {
                formula = ComposeFormula(tree);
            }
            return formula;
        }

        private string ComposeFormula(ParseNode node)
        {
            string combiner = string.Empty;
            switch (node.Type)
            {
                case PropType.Atom:
                    return node.Atom.Name;
                case PropType.Not:
                    return string.Concat("~(", ComposeFormula(node[0]), ")");
                case PropType.And:
                    combiner = "∧";
                    break;
                case PropType.Imply:
                    combiner = "→";
                    break;
                default:
                    break;
            }

            string pre = ComposeFormula(node[0]);
            string post = ComposeFormula(node[1]);
            if (pre.Length > 1 && pre[0] != '~') pre = "(" + pre + ")";
            if (post.Length > 1 && post[0] != '~') post = "(" + post + ")";

            return (pre + combiner + post);
        }

        private bool CalculateFormula(ParseNode node)
        {
            string combiner = string.Empty;
            switch (node.Type)
            {
                case PropType.Atom:
                    return node.Atom.Value;
                case PropType.Not:
                    return !CalculateFormula(node[0]);
                case PropType.And:
                    return (CalculateFormula(node[0]) && CalculateFormula(node[1]));
                case PropType.Imply:
                    return (!CalculateFormula(node[0]) || CalculateFormula(node[1]));
                default:
                    break;
            }

            return false;
        }

        #endregion

        #region Properties

        public ParseNode ParseTree
        {
            set
            {
                tree = value;
                formula = string.Empty;
            }
        }

        public bool Value
        {
            get { return CalculateFormula(tree); }
        }

        #endregion

        #region Data members

        private string formula;
        private ParseNode tree;

        #endregion

        // private IList<>
    }

    class ParseNode
    {
        public ParseNode(PropType type)
        {
            this.type = type;
            atom = null;
            switch (type)
            {
                case PropType.Atom: //Atom has no child node
                    break;
                case PropType.Not:// Not has only one child node
                    childNodes = new List<ParseNode>(1) { null };
                    break;
                case PropType.And:
                case PropType.Imply://And & Imply have two child nodes
                    childNodes = new List<ParseNode>(2) { null, null };
                    break;
                default:
                    break;
            }
        }

        #region Properties

        public Atom Atom
        {
            get { return atom; }
            set
            {
                if (type != PropType.Atom)
                    throw new Exception("This node is not atom");
                atom = value;
            }
        }

        public ParseNode this[int index]
        {
            get
            {
                return childNodes[index];
            }
            set
            {
                childNodes[index] = value;
            }

        }

        public PropType Type { get { return type; } }

        #endregion

        #region data members

        private PropType type;
        private IList<ParseNode> childNodes;
        private Atom atom;
        #endregion
    }
}
