import re

class Node:
    pass

class AssignmentNode(Node):
    def _init_(self, var_name, expr):
        self.var_name = var_name
        self.expr = expr

class BinaryOpNode(Node):
    def _init_(self, left, right, op):
        self.left = left
        self.right = right
        self.op = op

class ConstantNode(Node):
    def _init_(self, value):
        self.value = value

class VariableNode(Node):
    def _init_(self, name):
        self.name = name

def tokenize(expression):
    tokens = re.findall(r'\d+|[a-zA-Z_]\w*|[+\-*/=]', expression)
    return tokens

def parse(tokens):
    if '=' in tokens:
        var_name = tokens[0]
        expr_tokens = tokens[2:]  # Skip the '='
        expr = parse_expression(expr_tokens)
        return AssignmentNode(var_name, expr)

def parse_expression(tokens):
    left = ConstantNode(int(tokens[0])) if tokens[0].isdigit() else VariableNode(tokens[0])
    operator = tokens[1]
    right = ConstantNode(int(tokens[2])) if tokens[2].isdigit() else VariableNode(tokens[2])
    return BinaryOpNode(left, right, operator)

class CodeGenerator:
    def _init_(self):
        self.code = []
        self.temp_counter = 0

    def generate(self, node):
        if isinstance(node, AssignmentNode):
            temp_var = self.generate(node.expr)
            self.code.append(f"MOV {node.var_name}, {temp_var}")
        elif isinstance(node, BinaryOpNode):
            left_var = self.generate(node.left)
            right_var = self.generate(node.right)
            temp_var = f"t{self.temp_counter}"
            self.temp_counter += 1
            self.code.append(f"ADD {left_var}, {right_var}")
            return temp_var
        elif isinstance(node, ConstantNode):
            return str(node.value)
        elif isinstance(node, VariableNode):
            return node.name

    def get_code(self):
        return "\n".join(self.code)

# Input handling
def main():
    expression = input("Enter an expression (e.g., a = 3 + 5): ")
    tokens = tokenize(expression)
    ast = parse(tokens)
    cg = CodeGenerator()
    cg.generate(ast)
    print("\nGenerated Machine Code:")
    print(cg.get_code())

if _name_ == "_main_":
    main()
