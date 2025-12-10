# ONNX Runtime 基本用法介绍

## 简介  

**ONNX Runtime (ORT)** 是一款高性能的推理引擎，能够运行 ONNX 模型并适配各种硬件平台。本指南将帮助您快速掌握 ONNX Runtime 的使用，涵盖从安装到推理执行的基础步骤。

### 学习内容  

- 如何加载 ONNX 模型  
- 如何准备输入数据  
- 如何配置推理选项以提高性能  
- 如何使用 ONNX Runtime 运行推理  

完成本指南后，您将能够选择一个模型，处理输入数据，并高效执行推理。

---

## 准备工作：安装 ONNX Runtime

在使用 ONNX Runtime 进行模型推理之前，需要先完成安装。详细安装步骤请参阅 **[ONNX Runtime 安装](https://gitlab.dc.com:8443/mastery-suite/spacemit-riscv-content/-/blob/main/docs/AI/01_AI%E5%9F%BA%E7%A1%80%E5%AD%A6%E4%B9%A0%E5%8F%8A%E5%AE%9E%E8%B7%B5/05_onnxruntime%E5%AE%89%E8%A3%85.md?ref_type=heads)**。

## 步骤 1：加载 ONNX 模型

安装完成 ONNX Runtime 后，可以通过 `onnxruntime.InferenceSession` 在 Python 中加载 ONNX 模型。在此，我们使用 `resnet18_Opset17.onnx` 模型的加载示例。示例模型 `resnet18_Opset17.onnx` 是一个已经训练好的图像分类AI模型，专门用来识别图片中的物体是什么。

```python
# import onnxruntime as ort
import numpy as np
import spacemit_ort  # SpaceMIT硬件专用加速库

# 模型路径 
model_path = "/home/musebook/resnet18_Opset17.onnx"

try:
    # 创建推理会话
    # 首次加载时会自动选择可用执行提供程序
    session = ort.InferenceSession(model_path)
    
    # 打印加载成功信息和可用硬件加速器
    print("模型加载成功!")
    print("可用执行提供程序:", ort.get_available_providers())
    
except Exception as e:
    print(f"模型加载失败: {e}")
    exit()
```

---

## 步骤 2：准备输入数据

在进行推理之前，需要准备符合模型输入要求的数据。首先，获取输入名称和尺寸，然后加载真实图片进行处理。以下是如何加载 `kitten.jpg` 图片并准备输入数据的代码：

```python
from PIL import Image  # 图像处理库

# 获取模型输入信息
input_name = session.get_inputs()[0].name    # 获取输入节点名称
input_shape = session.get_inputs()[0].shape  # 获取输入张量形状
print(f"输入名称: {input_name}, 形状: {input_shape}")

# 图像路径
img_path = "/home/musebook/kitten.jpg"

try:
    # 打开并预处理图像
    img = Image.open(img_path)
    img = img.resize((224, 224))  # 调整大小为模型需要的224x224
    
    # 将图像转换为模型需要的张量格式
    input_tensor = np.array(img).astype(np.float32) / 255.0  # 归一化到[0,1]
    input_tensor = np.transpose(input_tensor, (2, 0, 1))     # 从HWC转为CHW格式
    input_tensor = np.expand_dims(input_tensor, axis=0)      # 添加batch维度
    
    # 打印处理结果
    print(f"输入数据准备完成: {img_path}")
    print("输入张量示例值:", input_tensor[0, 0, 0, :5])  # 打印前5个像素值
    
except Exception as e:
    print(f"输入数据准备失败: {e}")
    exit()
```

此代码会将 `kitten.jpg` 图片调整为 224x224 的大小，并将像素值归一化后转换为符合 ResNet18 模型输入要求的格式。

---

## 步骤 3：配置推理引擎

为了提高推理效率，可以通过对推理 `session` 的参数设置来优化性能。其中，**Execution Providers (EP)** 是关键组件，用于指定模型运行时使用的计算设备和库。不同的硬件通常会有对应的 Execution Providers 来提供相应的硬件加速功能。

以下是配置推理引擎的示例代码。在本示例中，我们使用了 `SpaceMITExecutionProvider`，它为特定硬件提供了优化的推理性能。您可以根据实际硬件环境选择合适的 Execution Provider。

```python
# 创建会话配置对象
session_options = ort.SessionOptions()

# 设置并行计算线程数
session_options.intra_op_num_threads = 4  
session_options.inter_op_num_threads = 4  

try:
    # 使用SpaceMIT专用配置重新加载模型
    session = ort.InferenceSession(
        model_path,
        session_options,
        providers=["SpaceMITExecutionProvider"]  # 使用SpaceMIT硬件加速
    )
    print("SpaceMIT执行提供程序配置成功!")
    
except Exception as e:
    print(f"SpaceMIT配置失败: {e}")
    exit()
```

---

## 步骤 4：运行推理

可以通过 `session.run()` 执行推理，该方法需要两个参数：一个是输出名称列表，另一个是输入数据的字典：

```python
# 获取输出节点名称
output_name = session.get_outputs()[0].name
print(f"输出节点名称: {output_name}")

try:
    # 执行模型推理
    # 参数说明:
    # - 第一个参数: 需要获取的输出节点名称列表
    # - 第二个参数: 输入数据字典{输入节点名称: 输入张量}
    outputs = session.run([output_name], {input_name: input_tensor})
    
    # 解析输出结果
    predicted_class = np.argmax(outputs[0])  # 获取概率最高的类别索引
    print("推理完成!")
    print(f"预测类别索引: {predicted_class}")
    print("输出张量形状:", outputs[0].shape)  # 通常是(1, 1000)的图像分类结果
    
except Exception as e:
    print(f"推理执行失败: {e}")
    exit()
```

---

## 完整代码示例

以下是完整的 ONNX Runtime 推理代码示例，涵盖从加载模型到执行推理的全过程，并包含验证输出：

```python
# -*- coding: utf-8 -*-
"""
ONNX Runtime SpaceMIT硬件完整示例
功能: 加载模型 → 预处理图像 → SpaceMIT加速推理 → 输出结果
"""

# import onnxruntime as ort
import numpy as np
from PIL import Image
import spacemit_ort  # SpaceMIT硬件加速必须导入

def spacemit_demo():
    # ===== 步骤1: 加载模型 =====
    print("\n=== 步骤1: 加载模型 ===")
    model_path = "/home/musebook/resnet18_Opset17.onnx"  # 硬编码模型路径
    
    try:
        # 初始化ONNX Runtime会话
        session = ort.InferenceSession(model_path)
        print(f"模型加载成功: {model_path}")
        print("可用硬件加速:", ort.get_available_providers())
    except Exception as e:
        print(f"模型加载错误: {e}")
        return

    # ===== 步骤2: 准备输入 =====
    print("\n=== 步骤2: 准备输入数据 ===")
    input_name = session.get_inputs()[0].name  # 通常是"input"或"data"
    img_path = "/home/musebook/kitten.jpg"    # 硬编码图像路径
    
    try:
        # 图像预处理流水线
        img = Image.open(img_path)            # 1. 打开图像
        img = img.resize((224, 224))          # 2. 调整尺寸
        
        # 3. 转换为numpy数组并归一化
        input_tensor = np.array(img).astype(np.float32) / 255.0  
        
        # 4. 调整维度顺序 [H,W,C] -> [C,H,W]
        input_tensor = np.transpose(input_tensor, (2, 0, 1))  
        
        # 5. 添加batch维度 [C,H,W] -> [1,C,H,W]
        input_tensor = np.expand_dims(input_tensor, axis=0)    
        
        print("输入数据预处理完成")
        print(f"输入形状: {input_tensor.shape}")  # 应为(1, 3, 224, 224)
    except Exception as e:
        print(f"输入处理错误: {e}")
        return

    # ===== 步骤3: 配置SpaceMIT =====
    print("\n=== 步骤3: 配置SpaceMIT硬件 ===")
    
    # 创建优化配置对象
    opts = ort.SessionOptions()
    opts.intra_op_num_threads = 4  # 设置计算线程数
    opts.inter_op_num_threads = 4
    
    try:
        # 使用SpaceMIT专用配置重新初始化
        session = ort.InferenceSession(
            model_path,
            opts,
            providers=["SpaceMITExecutionProvider"]  # 关键: 指定硬件加速器
        )
        print("SpaceMIT加速器激活成功!")
    except Exception as e:
        print(f"SpaceMIT配置错误: {e}")
        return

    # ===== 步骤4: 执行推理 =====
    print("\n=== 步骤4: 运行推理 ===")
    output_name = session.get_outputs()[0].name
    
    try:
        # 执行推理计算
        outputs = session.run([output_name], {input_name: input_tensor})
        
        # 解析输出结果
        pred_class = np.argmax(outputs[0][0])  # 获取最高概率类别
        
        # ===== 显示结果 =====
        print("\n===== 推理结果 =====")
        print(f"预测类别ID: {pred_class}")
        print("输出张量形状:", outputs[0].shape)
        print("前5个类别概率:", outputs[0][0, :5])  # 显示前5个概率值
        
        # 显示输入图像 (需要图形界面支持)
        img.show(title=f"预测结果: {pred_class}")
        
    except Exception as e:
        print(f"推理执行错误: {e}")
        return

if __name__ == "__main__":
    spacemit_demo()
```

运行上述代码后，你将在终端看到各步骤的打印输出，如下图所示
![alt text](06-image.png)

通过本指南，你已经掌握了使用 ONNX Runtime 进行推理的完整流程。如果遇到问题，请检查你的安装是否正确，并确保 ONNX 模型兼容 ONNX Runtime。
