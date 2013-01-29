 /*
  * Copyright (C) 2007-2013 Frank Mertens.
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation; either version
  * 2 of the License, or (at your option) any later version.
  */

#include "SyntaxDebugger.hpp"

namespace ftl
{

namespace syntax
{

static void printChar(char ch) {
	if (ch < ' '/*32*/) {
		if (ch == '\t')
			print("\\t");
		else if (ch == '\n')
			print("\\n");
		else if (ch == '\f')
			print("\\f");
		else if (ch == '\r')
			print("\\r");
		else if (ch == 0)
			print("\\0");
		else
			print("\\%oct%", int(ToAscii<char>::map(ch)));
	}
	else if (ch < 127) {
		if (ch == '\\')
			print("\\");
		print("%%", ToAscii<char>::map(ch));
	}
	else if (ch < 256) {
		print("\\%oct%", ToUnicode<char>::map(ch));
	}
	else {
		print("\\x%hex%", ToUnicode<char>::map(ch));
	}
}

static void printString(char *s, int size) {
	for (int i = 0; i < size; ++i) {
		char ch = s[i];
		if (ch == '"')
			print("\\");
		printChar(s[i]);
	}
}

static void printString(const ByteArray &s) {
	printString(s.data(), s.size());
}

static void printCharAttr(char ch) {
	print("'");
	if (ch == '\'')
		print("\\");
	printChar(ch);
	print("'");
}

static void printStringAttr(const ByteArray &s) {
	print("\"");
	printString(s);
	print("\"");
}

void DebugNode::printNext(String indent)
{
	print("%%%%(", indent, declType());
	printAttributes(Format() << indent << debugger_->indent_);
	print(")");
}

void DebugNode::printBranch(Node *node, String indent) {
	if (node) {
		DebugNode *debugNode = cast<DebugNode>(node);
		if (debugNode) debugNode->printNext(indent);
		else print(indent);
	}
	else {
		print("%%PASS()", indent);
	}
}

String DebugNode::superIndent(String indent) const {
	return (indent != "") ? indent->copy(0, indent->size() - debugger_->indent_->size()) : indent;
}

String DebugNode::subIndent(String indent) const {
	return Format() << indent << DebugNode::debugger_->indent_;
}

class CharDebugNode: public DebugNode {
public:
	CharDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return charNode()->invert() ? "OTHER" : "CHAR"; }

	virtual void printAttributes(String indent) {
		printCharAttr(charNode()->ch());
	}

private:
	typedef syntax::CharNode CharNode;
	inline CharNode *charNode() const { return cast<CharNode>(DebugNode::entry()); }
};

class GreaterDebugNode: public DebugNode {
public:
	GreaterDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return greaterNode()->invert() ? "BELOW" : "GREATER"; }

	virtual void printAttributes(String index) {
		printCharAttr(greaterNode()->ch());
	}

private:
	typedef syntax::GreaterNode GreaterNode;
	inline GreaterNode *greaterNode() const { return cast<GreaterNode>(DebugNode::entry()); }
};

class GreaterOrEqualDebugNode: public DebugNode {
public:
	GreaterOrEqualDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return greaterOrEqualNode()->invert() ? "BELOW_OR_EQUAL" : "GREATER_OR_EQUAL"; }

	virtual void printAttributes(String index) {
		printCharAttr(greaterOrEqualNode()->ch());
	}

private:
	typedef syntax::GreaterOrEqualNode GreaterOrEqualNode;
	inline GreaterOrEqualNode *greaterOrEqualNode() const { return cast<GreaterOrEqualNode>(DebugNode::entry()); }
};

class AnyDebugNode: public DebugNode {
public:
	AnyDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "ANY"; }
};

class RangeMinMaxDebugNode: public DebugNode {
public:
	RangeMinMaxDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return rangeMinMaxNode()->invert() ? "EXCEPT" : "RANGE"; }

	virtual void printAttributes(String indent) {
		RangeMinMaxNode *node = rangeMinMaxNode();
		printCharAttr(node->a());
		print(", ");
		printCharAttr(node->b());
	}

private:
	typedef syntax::RangeMinMaxNode RangeMinMaxNode;
	inline RangeMinMaxNode *rangeMinMaxNode() const { return cast<RangeMinMaxNode>(DebugNode::entry()); }
};

class RangeExplicitDebugNode: public DebugNode {
public:
	RangeExplicitDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return rangeExplicitNode()->invert() ? "EXCEPT" : "RANGE"; }

	virtual void printAttributes(String indent) {
		printStringAttr(rangeExplicitNode()->s());
	}

private:
	typedef syntax::RangeExplicitNode RangeExplicitNode;
	inline RangeExplicitNode *rangeExplicitNode() const { return cast<RangeExplicitNode>(DebugNode::entry()); }
};

class StringDebugNode: public DebugNode {
public:
	StringDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "STRING"; }

	virtual void printAttributes(String indent) {
		printStringAttr(stringNode()->s());
	}

private:
	typedef syntax::StringNode StringNode;
	inline StringNode *stringNode() const { return cast<StringNode>(DebugNode::entry()); }
};

class KeywordDebugNode: public DebugNode {
public:
	KeywordDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "KEYWORD"; }

	virtual void printAttributes(String indent) {
		print("\n%%\"", indent);
		KeywordMap *map = keywordNode()->map();
		for (KeywordMap::Index index = map->first(); map->has(index); ++index) {
			O<KeywordMap::Key> s = map->key(index);
			printString(*s);
			if (index != map->last())
				print(" ");
		}
		print("\"\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::KeywordNode KeywordNode;
	typedef syntax::KeywordMap KeywordMap;
	inline KeywordNode *keywordNode() const { return cast<KeywordNode>(DebugNode::entry()); }
};

class RepeatDebugNode: public DebugNode {
public:
	RepeatDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "REPEAT"; }

	virtual void printAttributes(String indent) {
		RepeatNode *node = repeatNode();
		if (node->maxRepeat() != intMax)
			print("%%, %%,", node->minRepeat(), node->maxRepeat());
		else if (node->minRepeat() != 0)
			print("%%,", node->minRepeat());
		print("\n");
		printBranch(node->entry(), indent);
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::RepeatNode RepeatNode;
	inline RepeatNode *repeatNode() const { return cast<RepeatNode>(DebugNode::entry()); }
};

class LazyRepeatDebugNode: public DebugNode {
public:
	LazyRepeatDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "LAZY_REPEAT"; }

	virtual void printAttributes(String indent) {
		LazyRepeatNode *node = repeatNode();
		if (node->minRepeat() != 0)
			print("%%,", node->minRepeat());
		print("\n");
		printBranch(node->entry(), indent);
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::LazyRepeatNode LazyRepeatNode;
	inline LazyRepeatNode *repeatNode() const { return cast<LazyRepeatNode>(DebugNode::entry()); }
};

class GreedyRepeatDebugNode: public DebugNode {
public:
	GreedyRepeatDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "GREEDY_REPEAT"; }

	virtual void printAttributes(String indent) {
		GreedyRepeatNode *node = repeatNode();
		if (node->maxRepeat() != intMax)
			print("%%, %%,", node->minRepeat(), node->maxRepeat());
		else if (node->minRepeat() != 0)
			print("%%,", node->minRepeat());
		print("\n");
		printBranch(node->entry(), indent);
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::GreedyRepeatNode GreedyRepeatNode;
	inline GreedyRepeatNode *repeatNode() const { return cast<GreedyRepeatNode>(DebugNode::entry()); }
};

class LengthDebugNode: public DebugNode {
public:
	LengthDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "LENGTH"; }

	virtual void printAttributes(String indent) {
		LengthNode *node = lengthNode();
		if (node->maxLength() != intMax)
			print("%%, %%,\n", node->minLength(), node->maxLength());
		else
			print("%%,\n", node->minLength());
		printBranch(node->entry(), indent);
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::LengthNode LengthNode;
	inline LengthNode *lengthNode() const { return cast<LengthNode>(DebugNode::entry()); }
};

class BoiDebugNode: public DebugNode {
public:
	BoiDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "BOI"; }
};

class EoiDebugNode: public DebugNode {
public:
	EoiDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "EOI"; }
};

class PassDebugNode: public DebugNode {
public:
	PassDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return passNode()->invert() ? "FAIL" : "PASS"; }

private:
	typedef syntax::PassNode PassNode;
	inline PassNode *passNode() const { return cast<PassNode>(DebugNode::entry()); }
};

class FindDebugNode: public DebugNode {
public:
	FindDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "FIND"; }

	virtual void printAttributes(String indent) {
		print("\n");
		printBranch(findNode()->entry(), indent);
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::FindNode FindNode;
	inline FindNode *findNode() const { return cast<FindNode>(DebugNode::entry()); }
};

class AheadDebugNode: public DebugNode {
public:
	AheadDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return aheadNode()->invert() ? "NOT" : "AHEAD"; }

	virtual void printAttributes(String indent) {
		print("\n");
		printBranch(aheadNode()->entry(), indent);
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::AheadNode AheadNode;
	inline AheadNode *aheadNode() const { return cast<AheadNode>(DebugNode::entry()); }
};

class BehindDebugNode: public DebugNode {
public:
	BehindDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return behindNode()->invert() ? "NOT_BEHIND" : "BEHIND"; }

	virtual void printAttributes(String indent) {
		print("\n");
		printBranch(behindNode()->entry(), indent);
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::BehindNode BehindNode;
	inline BehindNode *behindNode() const { return cast<BehindNode>(DebugNode::entry()); }
};

class ChoiceDebugNode: public DebugNode {
public:
	ChoiceDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "CHOICE"; }

	virtual void printAttributes(String indent) {
		print("\n");
		Node *node = choiceNode()->firstChoice();
		while (node) {
			printBranch(node, indent);
			node = node->nextSibling();
			if (node) print(",\n");
		}
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::ChoiceNode ChoiceNode;
	inline ChoiceNode *choiceNode() const { return cast<ChoiceNode>(DebugNode::entry()); }
};

class GlueDebugNode: public DebugNode {
public:
	GlueDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "GLUE"; }

	virtual void printAttributes(String indent) {
		print("\n");
		Node *node = glueNode()->firstChild();
		while (node) {
			printBranch(node, indent);
			node = node->nextSibling();
			if (node) print(",\n");
		}
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::GlueNode GlueNode;
	inline GlueNode *glueNode() const { return cast<GlueNode>(DebugNode::entry()); }
};

class HintDebugNode: public DebugNode {
public:
	HintDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return hintNode()->text() ? "HINT" : "DONE"; }

	virtual void printAttributes(String indent) {
		if (hintNode()->text())
			print("\"%%\"", hintNode()->text());
	}

private:
	typedef syntax::HintNode HintNode;
	inline HintNode *hintNode() const { return cast<HintNode>(DebugNode::entry()); }
};

class RefDebugNode: public DebugNode {
public:
	RefDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return (inlineNode()) ? "INLINE" : "REF"; }

	virtual void printAttributes(String indent) {
		print("\"%%\"", linkNode()->ruleName());
	}

private:
	typedef syntax::LinkNode LinkNode;
	inline LinkNode *linkNode() const { return cast<LinkNode>(DebugNode::entry()); }

	typedef syntax::InlineNode InlineNode;
	inline InlineNode *inlineNode() const { return cast<InlineNode>(DebugNode::entry()); }
};

class InlineDebugNode: public DebugNode {
public:
	InlineDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "INLINE"; }

	virtual void printAttributes(String indent) {
		print("\"%%\"", inlineNode()->ruleName());
	}

private:
	typedef syntax::InlineNode InlineNode;
	inline InlineNode *inlineNode() const { return cast<InlineNode>(DebugNode::entry()); }
};

class PreviousDebugNode: public DebugNode {
public:
	PreviousDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "PREVIOUS"; }

	virtual void printAttributes(String indent) {
		PreviousNode *node = previousNode();
		print("\"%%\"", node->ruleName());
		if (node->keywordName())
			print(", \"%%\"", node->keywordName());
	}

private:
	typedef syntax::PreviousNode PreviousNode;
	inline PreviousNode *previousNode() const { return cast<PreviousNode>(DebugNode::entry()); }
};

class CallDebugNode: public DebugNode {
public:
	CallDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "CALL"; }

	virtual void printAttributes(String indent) {
		print("0x%hex:8.:'0'", (void *)callNode()->callBack());
	}

private:
	typedef syntax::CallNode CallNode;
	inline CallNode *callNode() const { return cast<CallNode>(DebugNode::entry()); }
};

class SetDebugNode: public DebugNode {
public:
	SetDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "SET"; }

	virtual void printAttributes(String indent) {
		SetNode *node = setNode();
		print("\"%%\", %%", DebugNode::debugger_->flagNameById()->value(node->flagId()), node->value());
	}

private:
	typedef syntax::SetNode SetNode;
	inline SetNode *setNode() const { return cast<SetNode>(DebugNode::entry()); }
};

class IfDebugNode: public DebugNode {
public:
	IfDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "IF"; }

	virtual void printAttributes(String indent) {
		IfNode *node = ifNode();
		print("\"%%\",\n", DebugNode::debugger_->flagNameById()->value(node->flagId()));
		printBranch(node->trueBranch(), indent);
		print(",\n");
		printBranch(node->falseBranch(), indent);
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::IfNode IfNode;
	inline IfNode *ifNode() const { return cast<IfNode>(DebugNode::entry()); }
};

class CaptureDebugNode: public DebugNode {
public:
	CaptureDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "CAPTURE"; }

	virtual void printAttributes(String indent) {
		CaptureNode *node = captureNode();
		print("\"%%\",\n", DebugNode::debugger_->captureNameById()->value(node->captureId()));
		printBranch(node->coverage(), indent);
		print("\n%%", DebugNode::superIndent(indent));
	}

private:
	typedef syntax::CaptureNode CaptureNode;
	inline CaptureNode *captureNode() const { return cast<CaptureNode>(DebugNode::entry()); }
};

class ReplayDebugNode: public DebugNode {
public:
	ReplayDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "REPLAY"; }

	virtual void printAttributes(String indent) {
		print("\"%%\"", DebugNode::debugger_->captureNameById()->value(replayNode()->captureId()));
	}
private:
	typedef syntax::ReplayNode ReplayNode;
	inline ReplayNode *replayNode() const { return cast<ReplayNode>(DebugNode::entry()); }
};

class InvokeDebugNode: public DebugNode {
public:
	InvokeDebugNode(Debugger *debugger, Node *newNode)
		: DebugNode(debugger, newNode)
	{}

	virtual const char *declType() const { return "INVOKE"; }

	virtual void printAttributes(String indent) {
		InvokeNode *node = invokeNode();
		if (node->coverage()) {
			print("\"%%\",\n", node->definitionName());
			printBranch(node->coverage(), indent);
			print("\n%%", DebugNode::superIndent(indent));
		}
		else {
			print("\"%%\"", node->definitionName());
		}
	}

private:
	typedef syntax::InvokeNode InvokeNode;
	inline InvokeNode *invokeNode() const { return cast<InvokeNode>(DebugNode::entry()); }
};

Debugger::Debugger(String indent)
	: factoryByNodeType_(FactoryByNodeType::create()),
	  indent_(indent)
{
	factoryByNodeType_->insert("Char",           new DebugNodeFactory<CharDebugNode>           (this));
	factoryByNodeType_->insert("Greater",        new DebugNodeFactory<GreaterDebugNode>        (this));
	factoryByNodeType_->insert("GreaterOrEqual", new DebugNodeFactory<GreaterOrEqualDebugNode> (this));
	factoryByNodeType_->insert("Any",            new DebugNodeFactory<AnyDebugNode>            (this));
	factoryByNodeType_->insert("RangeMinMax",    new DebugNodeFactory<RangeMinMaxDebugNode>    (this));
	factoryByNodeType_->insert("RangeExplicit",  new DebugNodeFactory<RangeExplicitDebugNode>  (this));
	factoryByNodeType_->insert("String",         new DebugNodeFactory<StringDebugNode>         (this));
	factoryByNodeType_->insert("Keyword",        new DebugNodeFactory<KeywordDebugNode>        (this));
	factoryByNodeType_->insert("Repeat",         new DebugNodeFactory<RepeatDebugNode>         (this));
	factoryByNodeType_->insert("LazyRepeat",     new DebugNodeFactory<LazyRepeatDebugNode>     (this));
	factoryByNodeType_->insert("GreedyRepeat",   new DebugNodeFactory<GreedyRepeatDebugNode>   (this));
	factoryByNodeType_->insert("Length",         new DebugNodeFactory<LengthDebugNode>         (this));
	factoryByNodeType_->insert("Eoi",            new DebugNodeFactory<EoiDebugNode>            (this));
	factoryByNodeType_->insert("Boi",            new DebugNodeFactory<BoiDebugNode>            (this));
	factoryByNodeType_->insert("Pass",           new DebugNodeFactory<PassDebugNode>           (this));
	factoryByNodeType_->insert("Find",           new DebugNodeFactory<FindDebugNode>           (this));
	factoryByNodeType_->insert("Ahead",          new DebugNodeFactory<AheadDebugNode>          (this));
	factoryByNodeType_->insert("Behind",         new DebugNodeFactory<BehindDebugNode>         (this));
	factoryByNodeType_->insert("Choice",         new DebugNodeFactory<ChoiceDebugNode>         (this));
	factoryByNodeType_->insert("Glue",           new DebugNodeFactory<GlueDebugNode>           (this));
	factoryByNodeType_->insert("Hint",           new DebugNodeFactory<HintDebugNode>           (this));
	factoryByNodeType_->insert("Ref",            new DebugNodeFactory<RefDebugNode>            (this));
	factoryByNodeType_->insert("Inline",         new DebugNodeFactory<InlineDebugNode>         (this));
	factoryByNodeType_->insert("Previous",       new DebugNodeFactory<PreviousDebugNode>       (this));
	factoryByNodeType_->insert("Call",           new DebugNodeFactory<CallDebugNode>           (this));
	factoryByNodeType_->insert("Set",            new DebugNodeFactory<SetDebugNode>            (this));
	factoryByNodeType_->insert("If",             new DebugNodeFactory<IfDebugNode>             (this));
	factoryByNodeType_->insert("Capture",        new DebugNodeFactory<CaptureDebugNode>        (this));
	factoryByNodeType_->insert("Replay",         new DebugNodeFactory<ReplayDebugNode>         (this));
	factoryByNodeType_->insert("Invoke",         new DebugNodeFactory<InvokeDebugNode>         (this));
}

void Debugger::printDefinition(bool omitUnusedRules)
{
	if (omitUnusedRules)
		determineRulesInUse(DebugFactory::definition()->rule());

	typedef DefinitionNode::RuleByName RuleByName;
	typedef syntax::RuleNode RuleNode;
	RuleByName *ruleByName = DebugFactory::definition()->ruleByName_;

	typedef Map<int, RuleNode *> RuleById;
	O<RuleById> ruleById = RuleById::create();

	for (RuleByName::Index i = ruleByName->first(); ruleByName->has(i); ++i) {
		RuleNode *rule = ruleByName->value(i);
		ruleById->insert(rule->id(), rule);
	}

	for (int i = 0; i < ruleById->length(); ++i) {
		RuleNode *rule = ruleById->get(i).value();
		if (omitUnusedRules && !rule->used()) continue;
		print("DEFINE%%(\"%%\",\n", rule->isVoid() ? "_VOID" : "", rule->name());
		if (rule->entry()) {
			DebugNode *debugNode = cast<DebugNode>(rule->entry());
			if (debugNode) debugNode->printNext(indent_);
		}
		else {
			print("%%PASS()", indent_);
		}
		print("\n);\n\n");
	}

	print("ENTRY(\"%%\");\n", DebugFactory::definition()->ruleName_);
}

Node *Debugger::produce(Node *newNode, const char *nodeType)
{
	O<NodeFactory> factory;
	return factoryByNodeType_->lookup(nodeType, &factory) ? factory->produce(newNode) : newNode;
}

O<Debugger::StateNameById> Debugger::newReverseMap(StateIdByName *stateIdByName)
{
	O<StateNameById> stateNameById = StateNameById::create();
	for (StateIdByName::Index i = stateIdByName->first(); stateIdByName->has(i); ++i) {
		String name = stateIdByName->key(i);
		int id = stateIdByName->value(i);
		stateNameById->insert(id, name);
	}
	return stateNameById;
}

Debugger::StateNameById *Debugger::flagNameById() {
	if (!flagNameById_)
		flagNameById_ = newReverseMap(this->definition()->flagIdByName_);
	return flagNameById_;
}

Debugger::StateNameById *Debugger::captureNameById() {
	if (!captureNameById_)
		captureNameById_ = newReverseMap(this->definition()->captureIdByName_);
	return captureNameById_;
}

void Debugger::determineRulesInUse(RuleNode *rule)
{
	if (!rule->used()) {
		rule->markUsed();
		Node *node = rule->entry()->first();
		while (node) {
			LinkNode *link = cast<LinkNode>(node);
			if (link)
				determineRulesInUse(link->rule());
			node = node->next();
		}
	}
}

} // namespace syntax

} // namespace ftl